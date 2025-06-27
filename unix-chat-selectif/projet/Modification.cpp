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
#include "FichierUtilisateur.h"
int idQ,idSem;

struct sembuf operation[1];

int main()
{
  char nom[40];

  // Recuperation de l'identifiant de la file de messages
  fprintf(stderr,"(MODIFICATION %d) Recuperation de l'id de la file de messages\n",getpid());

  //!etape 5b
  if ((idQ = msgget(CLE,0)) == -1)
  {
      perror("(MODIFICATION)Erreur de msgget");
      exit(1);
  }

  // Recuperation de l'identifiant du sémaphore
  //!etape 5c
  if ((idSem = semget(CLE,0,0)) == -1)
  {
    perror("(MODIFICATION) Erreur de semget");
    exit(1);
  }

  MESSAGE m;
  // Lecture de la requête MODIF1
  fprintf(stderr,"(MODIFICATION %d) Lecture requete MODIF1\n",getpid());

  //!etape 5b
  if (msgrcv(idQ, &m, sizeof(MESSAGE) - sizeof(long), getpid(), 0) == -1) 
  {
        perror("(MODIFICATION) Erreur msgrcv-> MODIF1");
        exit(1);
  }

  // Tentative de prise non bloquante du semaphore 0 (au cas où un autre utilisateut est déjà en train de modifier)
  //!etape 5c
  
  operation[0].sem_num = 0; 
  operation[0].sem_op = -1; 
  operation[0].sem_flg = IPC_NOWAIT;//nb:prise non bloquante du semaphore

  if (semop(idSem, operation, 1) == -1)
  {
    strcpy(m.data1, "KO");
    strcpy(m.data2, "KO");
    strcpy(m.texte, "KO");

    m.type=m.expediteur;

    if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
    {
        perror("(MODIFICATION) Erreur de msgsnd ->MODIF1");
        exit(1);
    }

    exit(0);
  }


  // Connexion à la base de donnée
  MYSQL *connexion = mysql_init(NULL);
  fprintf(stderr,"(MODIFICATION %d) Connexion à la BD\n",getpid());
  if (mysql_real_connect(connexion,"localhost","Student","PassStudent1_","PourStudent",0,0,0) == NULL)
  {
    fprintf(stderr,"(MODIFICATION) Erreur de connexion à la base de données...\n");
    exit(1);  
  }

  // Recherche des infos dans la base de données
  fprintf(stderr,"(MODIFICATION %d) Consultation en BD pour --%s--\n",getpid(),m.data1);
  strcpy(nom,m.data1);
  MYSQL_RES  *resultat;
  MYSQL_ROW  tuple;
  char requete[200];
  // sprintf(requete,...);

  //!etape 5b
  sprintf(requete, "SELECT GSM, email FROM UNIX_FINAL WHERE nom='%s'", nom);

  mysql_query(connexion,requete);
  resultat = mysql_store_result(connexion);
  tuple = mysql_fetch_row(resultat); // user existe forcement

  // Construction et envoi de la reponse
  fprintf(stderr,"(MODIFICATION %d) Envoi de la reponse\n",getpid());
  //!etape 5b

  m.type = m.expediteur;
  strcpy(m.data1, "OK");
  strcpy(m.data2, tuple[0]); 
  strcpy(m.texte, tuple[1]); 

  if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
  {
      perror("(MODIFICATION) Erreur de msgsnd ->MODIF2");
      exit(1);
  }

  
  // Attente de la requête MODIF2
  fprintf(stderr,"(MODIFICATION %d) Attente requete MODIF2...\n",getpid());

  if (msgrcv(idQ, &m, sizeof(MESSAGE) - sizeof(long), getpid(), 0) == -1)
  {
        perror("(MODIFICATION) Erreur msgrcv -> MODIF2");
        exit(1);
  }

  // Mise à jour base de données
  fprintf(stderr,"(MODIFICATION %d) Modification en base de données pour --%s--\n",getpid(),nom);
  //sprintf(requete,...);
  //!etape 5b
  sprintf(requete, "UPDATE UNIX_FINAL SET  GSM='%s' WHERE nom='%s'",  m.data2, nom);

  mysql_query(connexion,requete);
  //sprintf(requete,...);
  //!etape 5b
  sprintf(requete, "UPDATE UNIX_FINAL SET   email='%s' WHERE nom='%s'",   m.texte, nom);

  mysql_query(connexion,requete);

  // Mise à jour du fichier si nouveau mot de passe
  sprintf(requete, "SELECT motdepasse FROM UNIX_FINAL WHERE nom='%s'", nom);
  
  if(strcmp(m.data1, "") != 0)
  {
    if(modifMotDePasse(nom,m.data1)!=1)
    {
      perror("(MODIFICATION) erreur mdp");
      exit(1);
    } 
  }

  // Deconnexion BD
  mysql_close(connexion);

  // Libération du semaphore 0
  fprintf(stderr,"(MODIFICATION %d) Libération du sémaphore 0\n",getpid());
  //!etape 5c

  operation[0].sem_op=1;

  if(semop(idSem, operation, 1)== -1)
  {
    perror("(MODIFICATION) erreur semop");
  }

  exit(0);
}
