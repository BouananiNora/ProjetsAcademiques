#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <mysql.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "protocole.h"

int idQ,idSem;
struct sembuf operation[1];
int main()
{
  // Recuperation de l'identifiant de la file de messages
  fprintf(stderr,"(CONSULTATION %d) Recuperation de l'id de la file de messages\n",getpid());

    //!etape 5a
    if ((idQ = msgget(CLE, 0)) == -1)
    {
        perror("(CONSULTATION)Erreur de msgget");
        exit(1);
    }

  //Recuperation de l'identifiant du sémaphore
  //!etape 5c
  if ((idSem = semget(CLE,0,0)) == -1)
  {
    perror("(CONSULTATION) Erreur de semget");
    exit(1);
  }

  MESSAGE m;
  // Lecture de la requête CONSULT
  fprintf(stderr,"(CONSULTATION %d) Lecture requete CONSULT\n",getpid());

    //!etape 5a

    if (msgrcv(idQ, &m, sizeof(MESSAGE) - sizeof(long), getpid(), 0) == -1)
    {
        perror("(CONSULTATION)Erreur de msgrcv");
        exit(1);
    } 

  // Tentative de prise bloquante du semaphore 0
  fprintf(stderr,"(CONSULTATION %d) Prise bloquante du sémaphore 0\n",getpid());

  //!etape 5c
  
  operation[0].sem_num = 0; 
  operation[0].sem_op = -1; 
  operation[0].sem_flg = 0; //nb:prise  bloquante du semaphore

  if (semop(idSem, operation, 1) == -1)
  {
    perror("(CONSULTATION) Erreur de semop");
  }

  // Connexion à la base de donnée
  MYSQL *connexion = mysql_init(NULL);
  fprintf(stderr,"(CONSULTATION %d) Connexion à la BD\n",getpid());
  if (mysql_real_connect(connexion,"localhost","Student","PassStudent1_","PourStudent",0,0,0) == NULL)
  {
    fprintf(stderr,"(CONSULTATION) Erreur de connexion à la base de données...\n");
    exit(1);  
  }

  // Recherche des infos dans la base de données
  fprintf(stderr,"(CONSULTATION %d) Consultation en BD (%s)\n",getpid(),m.data1);
  MYSQL_RES  *resultat;
  MYSQL_ROW  tuple;
  char requete[200];
  // sprintf(requete,...);
    //!etape 5a
  
    sprintf(requete, "SELECT gsm, email FROM UNIX_FINAL WHERE nom='%s';", m.data1);
  
  mysql_query(connexion,requete);
  resultat = mysql_store_result(connexion);
  // if ((tuple = mysql_fetch_row(resultat)) != NULL) ...
    //!etape 5a

    if ((tuple = mysql_fetch_row(resultat)) != NULL)
    {
        strcpy(m.data1, "OK");
        strcpy(m.data2, tuple[0]); 
        strcpy(m.texte, tuple[1]); 
    }
    else
    {
        strcpy(m.data1, "KO");
    }
    
  // Construction et envoi de la reponse
  //!etape 5a

    m.type = m.expediteur;
    
    if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1)
    {
        perror("(CONSULTATION)Erreur de msgsnd");
        exit(1);
    }

    kill(m.type, SIGUSR1);

  // Deconnexion BD
  mysql_close(connexion);

  // Libération du semaphore 0
  fprintf(stderr,"(CONSULTATION %d) Libération du sémaphore 0\n",getpid());
  //!etape 5c

  operation[0].sem_op=1;  //rq: liberation du semaphore en augmentant sa valeur
  
  if(semop(idSem, operation, 1) == -1 )
  {
    perror("(CONSULTATION) Erreur de semop");
  }

  exit(0);
}