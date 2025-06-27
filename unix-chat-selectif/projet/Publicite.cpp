#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "protocole.h" // contient la cle et la structure d'un message
#include <errno.h>
int idQ, idShm;
int fd;

//!etape 4
char* pShm;
void handlerSIGINT(int sig);

//!etape 6c
void handlerSIGUSR1(int sig);
int main()
{
  // Armement des signaux
  //!etape 4

  struct sigaction A;
  A.sa_handler = handlerSIGINT;
  A.sa_flags = 0;
  sigemptyset(&A.sa_mask);

  if(sigaction(SIGINT, &A, NULL)== -1)
  {
      perror("(PUBLICITE) Erreur de sigaction -> SIGINT");
      exit(1);
  }

  //!etape 6c
  struct sigaction B;
  B.sa_handler = handlerSIGUSR1;
  B.sa_flags = 0;
  sigemptyset(&B.sa_mask);

  if (sigaction(SIGUSR1, &B, NULL) == -1) 
  {
      perror("(PUBLICITE) Erreur de sigaction -> SIGUSR1");
      exit(1);
  }


  // Masquage de SIGINT
  sigset_t mask;
  sigaddset(&mask,SIGINT);
  sigprocmask(SIG_SETMASK,&mask,NULL);

  // Recuperation de l'identifiant de la file de messages
  fprintf(stderr,"(PUBLICITE %d) Recuperation de l'id de la file de messages\n",getpid());

  //!etape 4

  if ((idQ = msgget(CLE,0)) == -1)
  {
      perror("(PUBLICITE)Erreur de msgget");
      exit(1);
  }

  // Recuperation de l'identifiant de la mémoire partagée
  fprintf(stderr,"(PUBLICITE %d) Recuperation de l'id de la mémoire partagée\n",getpid());

  //!etape 4

  if ((idShm = shmget(CLE, 0, 0)) == -1) 
  {
      perror("(PUBLICITE) Erreur de shmget");
      exit(1);
  }

  // Attachement à la mémoire partagée

  //!etape 4

  
  if ((pShm = (char*)shmat(idShm,NULL,0)) == (char*)-1)
  {
    perror("(PUBLICITE)Erreur de shmat");
    exit(1);
  }

  
  // Ouverture du fichier de publicité

  //!etape 6c

  while (access("publicites.dat", F_OK) == -1) 
  {
        pause(); 
  }

  // //!etape 4

  if ((fd = open("publicites.dat", O_RDONLY)) == -1)
  {
      perror("(PUBLICITE) Erreur open");
      exit(1);
  }

  
  while(1)
  {
  	PUBLICITE pub;
    int rc;

    // Lecture d'une publicité dans le fichier

    //!etape 4     

    if ((rc = read(fd,&pub,sizeof(PUBLICITE))) == -1)
    {
        perror("(PUBLICITE) Erreur de read");
        exit(1);
    }
    if (rc == 0) 
    {
      lseek(fd, 0, SEEK_SET);//nb:si on arrive a la fin du fichier on reccomence
    }
    

    // Ecriture en mémoire partagée

    //!etape 4

    strcpy(pShm,pub.texte);

    // Envoi d'une requete UPDATE_PUB au serveur

    MESSAGE m;
    m.type = 1; 
    m.requete = UPDATE_PUB;

    if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1)
    {
        perror("(PUBLICITE) Erreur de msgsnd");
        exit(1);
    }

    // Attente de la réponse du serveur

    //!etape 4

    sleep(pub.nbSecondes);

  }
  
}

//-----------HANDELERS ---------------


void handlerSIGINT(int sig)
{
  fprintf(stderr,"(PUBLICITE) Signal sigint recu: %d",sig);

  close(fd);

  if (shmdt(pShm) == -1) 
  {
    perror("(PUBLICITE) Erreur de shmdt");
    exit(1);
  }

}

void handlerSIGUSR1(int sig) 
{
    fprintf(stderr, "(PUBLICITE) Signal SIGUSR1 r\n");
}
