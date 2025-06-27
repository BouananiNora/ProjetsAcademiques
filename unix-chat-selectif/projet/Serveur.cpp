#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <mysql.h>
#include <setjmp.h>
#include "protocole.h" // contient la cle et la structure d'un message
#include <cerrno>
#include "FichierUtilisateur.h"


int idQ,idShm,idSem,sigRecu;
TAB_CONNEXIONS *tab;
char *pShm;
void afficheTab();

MYSQL* connexion;

void handlerSIGINT(int sig);
void handlerSIGCHLD(int sig);


int main()
{
  // Connection à la BD
  connexion = mysql_init(NULL);
  if (mysql_real_connect(connexion,"localhost","Student","PassStudent1_","PourStudent",0,0,0) == NULL)
  {
    fprintf(stderr,"(SERVEUR) Erreur de connexion à la base de données...\n");
    exit(1);  
  }
  

  // Armement des signaux

  //!etape 1a
  struct sigaction B;
  B.sa_handler = handlerSIGINT;
  B.sa_flags = 0;
  sigemptyset(&B.sa_mask);
  
  if(sigaction(SIGINT, &B, NULL)==-1)
  {
    perror("(SERVEUR) erreur de SIGINT");
    exit(1);
  }

  //!etape 5b
  struct sigaction C;
  C.sa_handler = handlerSIGCHLD;
  C.sa_flags = 0;
  sigemptyset(&C.sa_mask);
  
  if(sigaction(SIGCHLD ,&C, NULL)==-1)
  {
    perror("(SERVEUR) erreur de SIGCHLD");
    exit(1);
  }


  // Creation des ressources
  fprintf(stderr,"(SERVEUR %d) Creation de la file de messages\n",getpid());

  if ((idQ = msgget(CLE,IPC_CREAT | IPC_EXCL | 0600)) == -1)  
  {
    perror("(SERVEUR) Erreur de msgget");
    exit(1);
  }

  //!etape 5c
  if ((idSem = semget(CLE, 1, IPC_CREAT | IPC_EXCL | 0600)) == -1) 
  {
      perror("(SERVEUR) Erreur de semget");
      exit(1);
  }

  //!etape 5c
  if (semctl(idSem, 0, SETVAL, 1) == -1) 
  {
      perror("(SERVEUR) Erreur de semctl ");
      exit(1);
  }


  //!etape 4
  if ((idShm = shmget(CLE, 200, IPC_CREAT | IPC_EXCL | 0600)) == -1)  
  {
    perror("(SERVEUR) Erreur de shmget");
    exit(1);
  }

  //!etape 4

  if ((pShm = (char*)shmat(idShm,NULL,0)) == (char*)-1)
  {
    perror("Erreur de shmat");
    exit(1);
  }

  
  
  // Initialisation du tableau de connexions
  fprintf(stderr,"(SERVEUR %d) Initialisation de la table des connexions\n",getpid());
  tab = (TAB_CONNEXIONS*) malloc(sizeof(TAB_CONNEXIONS)); 

  for (int i=0 ; i<6 ; i++)
  {
    tab->connexions[i].pidFenetre = 0;
    strcpy(tab->connexions[i].nom,"");
    for (int j=0 ; j<5 ; j++) tab->connexions[i].autres[j] = 0;
    tab->connexions[i].pidModification = 0;
  }
  tab->pidServeur1 = getpid();
  tab->pidServeur2 = 0;
  tab->pidAdmin = 0;
  tab->pidPublicite = 0;
  
  afficheTab();

  // Creation du processus Publicite

  //!etape 4
  int pidPub;

  if((pidPub = fork())== -1)
  {
    perror("(SERVEUR) Ereur de fork ->Pub");
    exit(1);
  }

  if(pidPub == 0)    //nb:fils
  {
    if(execl("./Publicite","Publicite",NULL)==-1)
    {
      perror("(SERVEUR) Ereur de excel ->Pub");
      exit(1);
    }
  }
  else
  {
    tab->pidPublicite = pidPub;   //nb:pere
  }


  int i,k,j;
  MESSAGE m;
  MESSAGE reponse;
  char requete[200];
  MYSQL_RES  *resultat;
  MYSQL_ROW  tuple;
  PUBLICITE pub;
  int trouve,dejaLog,pos,ok,g,l, pidConsult,pidModif,msgrc,fdExist,fd;


  while(1)
  {
    fprintf(stderr,"(SERVEUR %d) Attente d'une requete...\n",getpid());
    msgrc=-1;

    //!etape 5b
    while((msgrc=msgrcv(idQ,&m,sizeof(MESSAGE)-sizeof(long),1,0)) == -1 && errno==EINTR && sigRecu==0)
    {}

    if( msgrc==-1)
    {
      perror("(SERVEUR) Erreur de msgrcv");
      exit(1);
    }


    switch(m.requete)
    {
      case CONNECT :  //!etape 1a

                      i=0;
                      trouve=0;

                      while(i<6  && trouve !=1 )
                      {
                        if(tab->connexions[i].pidFenetre == 0)
                        {
                          tab->connexions[i].pidFenetre = m.expediteur;;
                          trouve=1;
                        }
                        else
                        {
                          i++;
                        }
                      }

                      if(!trouve)
                      {
                        fprintf(stderr,"(SERVEUR %d) Pas de place disponible pour cette connexion\n",getpid());
                      }


                      fprintf(stderr,"(SERVEUR %d) Requete CONNECT reçue de %d\n",getpid(),m.expediteur);
                      break; 

      case DECONNECT : //!etape 1a
                      
                      i=0;
                      trouve=0;

                      while(i<6)
                      {
                        if(tab->connexions[i].pidFenetre == m.expediteur)
                        {
                          tab->connexions[i].pidFenetre = 0;
                          trouve=1;
                        }
                        else
                        {
                          i++;
                        }
                      }
                

                      fprintf(stderr,"(SERVEUR %d) Requete DECONNECT reçue de %d\n",getpid(),m.expediteur);
                      break; 

      case LOGIN :    //!etape 1b
                      
                      pos= estPresent(m.data2);  //nb: estPresnt renvoi une valeur positif si User existant

                      if(strcmp(m.data1,"1")==0)   //nb: Nouveau User
                      {
                          if(pos<=0)            //nb: ajout User
                          {
                            ajouteUtilisateur(m.data2,m.texte); //nb: ajout du nv User dans le fichier
                            strcpy(m.data1,"OK");
                            strcpy(m.texte,"User enregistrer");

                            //!etape 5.0
                            sprintf(requete,"INSERT INTO UNIX_FINAL VALUES (NULL,'%s','---','---')",m.data2); //nb: ajout du nv User dans la bd
                            mysql_query(connexion,requete);

                            i=0;
                            trouve=0;

                            while(i<6 && trouve !=1)
                            {
                                if(tab->connexions[i].pidFenetre == m.expediteur)
                                {
                                  strcpy(tab->connexions[i].nom,m.data2);   //nb: ajout User dans la tab de cnx
                                  trouve=1;
                                }
                                else
                                {
                                  i++;
                                }
                            }
                          }
                          else        //nb:User deja present
                          {
                            strcpy(m.data1,"KO");
                            strcpy(m.texte,"User existant");
                          }
                      }
                      else                      //nb: Login
                      {
                          if(pos>0) //nb: Login existant
                          {
                            i=0;
                            dejaLog = 0;

                            while(i<6 && dejaLog!=1)  //nb: Verif nom dans la tab de conx
                            {
                              if(strcmp(tab->connexions[i].nom ,m.data2)==0)
                              {
                                dejaLog = 1;
                              }
                              else
                              {
                                i++;
                              }
                            }

                            if(verifieMotDePasse(pos,m.texte))  //nb: mdp correct
                            {
                              if(!dejaLog)    //nb:User pas dans la tab de conx
                              {
                                i=0;
                                trouve=0;

                                while(i<6 && trouve !=1)
                                {
                                    if(tab->connexions[i].pidFenetre == m.expediteur)
                                    {
                                      strcpy(tab->connexions[i].nom,m.data2);   //nb: ajout User dans la tab de cnx
                                      trouve=1;
                                      strcpy(m.data1,"OK");
                                      strcpy(m.texte,"Connexion reussi");
                                    }
                                    else
                                    {
                                      i++;
                                    }
                                }
                                
                              }
                              else      //nb: User deja dans la tab de cnx
                              {
                                  strcpy(m.data1,"KO");
                                  strcpy(m.texte,"user deja connecter");
                              }
                            }
                            else                          //nb: mdp incorrect
                            {
                                strcpy(m.data1,"KO");
                                strcpy(m.texte,"Mdp incorect");
                            }
                          }
                          else                //nb: login incorrect
                          {
                            strcpy(m.data1,"KO");
                            strcpy(m.texte,"Login incorect");
                          }

                      }

                      m.type=m.expediteur;
                      

                      if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0)==-1)
                      {
                        perror("(SERVEUR) Erreur de msgsnd->LOGIN");
                        exit(1);
                      }


                      kill(m.type, SIGUSR1);
                      
                      //!etape 2a
                      
                      if (strcmp(m.data1,"OK") == 0) 
                      {
                          //nb:  informer les autres Users  du nv User
                          for (int j=0; j<6; j++) 
                          {
                              if (strcmp(tab->connexions[j].nom,"") != 0 && strcmp(tab->connexions[j].nom,m.data2) != 0)
                              {
                                  m.type = tab->connexions[j].pidFenetre;
                                  m.requete = ADD_USER;
                                  strcpy(m.data1, m.data2);  

                                  if (msgsnd(idQ, &m, sizeof(MESSAGE)-sizeof(long), 0)== -1) 
                                  {
                                      perror("(SERVEUR)Erreur de msgsnd ->LOGIN -> ADD_USER");
                                      exit(1);
                                  }

                                  kill(m.type, SIGUSR1);
                              }
                          }

                          //nb: informer a l'User la liste des autres Users
                          for (int j=0; j<6; j++)  
                          {
                              if (strcmp(tab->connexions[j].nom,"") != 0 && strcmp(tab->connexions[j].nom,m.data2) != 0)
                              {
                                  
                                  m.type = m.expediteur;
                                  m.requete = ADD_USER;
                                  strcpy(m.data1, tab->connexions[j].nom);  

                                  if (msgsnd(idQ, &m, sizeof(MESSAGE)-sizeof(long), 0)== -1) 
                                  {
                                      perror("(SERVEUR)Erreur de msgsnd ->LOGIN -> ADD_USER");
                                      exit(1);
                                  }

                                  kill(m.type, SIGUSR1);
                              }
                          }
                      }


                      fprintf(stderr,"(SERVEUR %d) Requete LOGIN reçue de %d : --%s--%s--%s--\n",getpid(),m.expediteur,m.data1,m.data2,m.texte);
                      break; 

      case LOGOUT :  //!etape 1b

                      i=0;
                      trouve=0;

                      while(i<6 && trouve!=1)
                      {
                        if(tab->connexions[i].pidFenetre == m.expediteur)
                        {
                          strcpy(tab->connexions[i].nom,"");      //nb:vide le nom de l'User dans le serveur
                          trouve=1;

                          //!etape 2b
                          for(l=0;l<6;l++)
                          {
                            tab->connexions[i].autres[l]=0;   //nb:vide la liste des autres users de luser concerner
                          }

                          //!etape 2a
                          

                          for (int j=0; j<6; j++) 
                          {
                              if (strcmp(tab->connexions[j].nom,"") != 0 && strcmp(tab->connexions[j].nom,m.data1) != 0)
                              {
                                  m.type = tab->connexions[j].pidFenetre;   
                                  m.requete = REMOVE_USER;      //nb: vider la liste des perso conn

                                  if (msgsnd(idQ, &m, sizeof(MESSAGE)-sizeof(long), 0)== -1) 
                                  {
                                      perror("(SERVEUR)Erreur de msgsnd ->LOGOUT-> ADD_USER");
                                  }
                                  
                                  kill(m.type,SIGUSR1);
                                  ok=0;
                                  while(k<6 && ok!=1)
                                  {
                                    if(tab->connexions[j].autres[k]==m.expediteur)
                                    {
                                      tab->connexions[j].autres[k] = 0;   //nb:supp l'User dans la liste des autres Users    
                                      ok=1;
                                    }
                                    else
                                    {
                                      k++;
                                    }
                                  }
                              }
                          }

                        }
                        else{
                          i++;
                        }
                      }

                      fprintf(stderr,"(SERVEUR %d) Requete LOGOUT reçue de %d\n",getpid(),m.expediteur);
                      break;

      case ACCEPT_USER : //!etape 2b

                        i = 0;
                        ok= 0;
                        trouve = 0;

                        while (i < 6 && trouve!=1)    //nb: on cherche l'expediteur
                        {
                            if (tab->connexions[i].pidFenetre == m.expediteur)  
                            {
                                trouve =1;

                                j =0;
                                while (j < 6 && ok!=1)  //nb: on cherche l'User accepter
                                {
                                    if (strcmp(tab->connexions[j].nom,m.data1) == 0) 
                                    {
                                        ok =1;

                                        k =0;
                                        g=0;
                                        while (k < 5 && g!=1)   //nb:on cherche un emplacemnt vide pour ajouter user accepter
                                        {
                                          if (tab->connexions[i].autres[k] == 0) 
                                          {
                                              g=1;
                                              tab->connexions[i].autres[k] = tab->connexions[j].pidFenetre;

                                          }
                                          else
                                          {
                                              k++;
                                          }
                                      }

                                    }
                                    else
                                    {
                                        j++;
                                    }
                                }
                            }
                            else
                            {
                                i++;
                            }
                        }


                      fprintf(stderr,"(SERVEUR %d) Requete ACCEPT_USER reçue de %d\n",getpid(),m.expediteur);
                      break;

      case REFUSE_USER :i = 0;
                        ok= 0;
                        trouve = 0;

                        while (i < 6 && trouve!=1)    //nb: on cherche l'expediteur
                        {
                            if (tab->connexions[i].pidFenetre == m.expediteur)  
                            {
                                trouve =1;

                                j =0;
                                while (j < 6 && ok!=1)  //nb: on cherche l'User accepter
                                {
                                    if (strcmp(tab->connexions[j].nom,m.data1) == 0) 
                                    {
                                        ok =1;

                                        k =0;
                                        g=0;
                                        while (k < 5 && g!=1)   //nb:on cherche un emplacemnt vide pour ajouter user accepter
                                        {
                                          if (tab->connexions[i].autres[k] == tab->connexions[j].pidFenetre) 
                                          {
                                              g=1;
                                              tab->connexions[i].autres[k] = 0;

                                          }
                                          else
                                          {
                                              k++;
                                          }
                                      }

                                    }
                                    else
                                    {
                                        j++;
                                    }
                                }
                            }
                            else
                            {
                                i++;
                            }
                        }

                      fprintf(stderr,"(SERVEUR %d) Requete REFUSE_USER reçue de %d\n",getpid(),m.expediteur);
                      break;

      case SEND :   //!etape 2c
                        i = 0;
                        trouve = 0;

                        while (i < 6 && trouve!=1)    //nb: on cherche l'expediteur
                        {
                            if (tab->connexions[i].pidFenetre == m.expediteur)  
                            {
                                trouve =1;

                                m.type = m.expediteur;              //nb: envoie de msg a nous meme (notre msg apparait aussi sur notre fenetre)
                                m.requete = SEND;
                                strcpy(m.data1, tab->connexions[i].nom);                                 
                                
                                if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
                                {
                                    perror("(SERVEUR) Erreur de msgsnd -> SEND");
                                    exit(1);
                                }

                                kill(m.type, SIGUSR1); 
                                
                                for (j =0; j< 6; j++) 
                                {
                                  if (tab->connexions[i].autres[j] !=0)
                                  { 
                                      
                                    m.type = tab->connexions[i].autres[j];       //nb: envoie de msg a la personne accepter
                                
                                    if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
                                    {
                                        perror("(SERVEUR) Erreur de msgsnd -> SEND");
                                    }
                                    
                                    
                                    kill(m.type, SIGUSR1);
                                    
                                      
                                  }
                              }

                            }
                            else
                            {
                              i++;
                            }
                          
                        }
                      
                      
                      fprintf(stderr,"(SERVEUR %d) Requete SEND reçue de %d\n",getpid(),m.expediteur);
                      break; 

      case UPDATE_PUB ://!etape 4

                      for (int j=0; j<6; j++) 
                      {
                          if (tab->connexions[j].pidFenetre != 0) 
                          {
                              kill(tab->connexions[j].pidFenetre, SIGUSR2);
                          }
                      }

                      fprintf(stderr,"(SERVEUR %d) Requete UPDATE_PUB reçue de %d\n",getpid(),m.expediteur);
                      break;


      case CONSULT :  //!etape 5a
                      
                      
                      if((pidConsult = fork())== -1)
                      {
                        perror("(SERVEUR) Ereur de fork ->Consultation");
                        exit(1);
                      }

                      if(pidConsult == 0)    //nb:fils
                      {
                        if(execl("./Consultation","Consultaion",NULL)==-1)
                        {
                          perror("(SERVEUR) Ereur de excel ->Consultaion");
                          exit(1);
                        }
                      }
                      
                      m.type=pidConsult;

                      if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
                      {
                          perror("(SERVEUR) Erreur de msgsnd ->Consultation");
                          exit(1);
                      }
                      

                      fprintf(stderr,"(SERVEUR %d) Requete CONSULT reçue de %d\n",getpid(),m.expediteur);
                      break;


      case MODIF1 : //!etape 5b

                      i =0;
                      trouve = 0;

                      while (i<6 && trouve!=1)
                      {
                        if (strcmp(tab->connexions[i].nom,m.data1)==0)
                        {
                          trouve =1;
                        }
                        else
                        {
                          i++;
                        }
                      }
                      
                      if (trouve == 1)
                      {
                          pidModif = fork();

                          if (pidModif == -1) 
                          {
                              perror("(SERVEUR) Erreur de fork -> MODIF1");
                              exit(1);
                          }

                          if (pidModif == 0) 
                          {
                              if(execl("./Modification", "Modification", NULL)==-1)
                              {
                                perror("(SERVEUR) Erreur de execl -> MODIF1");
                                exit(1);
                              }
                          } 
                          
                          tab->connexions[i].pidModification = pidModif;

                          m.type=pidModif;

                          if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1)
                          {
                            perror("(SERVEUR) Erreur de msgsnd -> MODIF1");
                            exit(1);
                          }

                          
                          }
                          
                      

                      fprintf(stderr,"(SERVEUR %d) Requete MODIF1 reçue de %d\n",getpid(),m.expediteur);
                      break;


      case MODIF2 ://!etape 5b
                      
                      i=0;
                      trouve=0;

                      while(i<6 && trouve !=1)
                      {
                        if(tab->connexions[i].pidFenetre==m.expediteur)
                        {
                          trouve=1;
                        }
                        else
                        {
                          i++;
                        }
                      }

                      if(trouve)
                      {
                        m.type= tab->connexions[i].pidModification;

                        if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1)
                        {
                          perror("(SERVEUR) Erreur de msgsnd -> MODIF2");
                          exit(1);
                        }
                      }
                      fprintf(stderr,"(SERVEUR %d) Requete MODIF2 reçue de %d\n",getpid(),m.expediteur);
                      break;

      case LOGIN_ADMIN ://!etape 6a

                        if (tab->pidAdmin == 0) 
                        {
                            tab->pidAdmin = m.expediteur;
                            strcpy(m.data1, "OK");
                        } 
                        else 
                        {
                            strcpy(m.data1, "KO");
                        }
                        
                        m.type = m.expediteur;

                        if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
                        {
                            perror("(SERVEUR) Erreur de msgsnd -> LOGIN_ADMIN");
                            exit(1);
                        }



                      fprintf(stderr,"(SERVEUR %d) Requete LOGIN_ADMIN reçue de %d\n",getpid(),m.expediteur);
                      break;

      case LOGOUT_ADMIN ://!etape 6a

                      if (tab->pidAdmin == m.expediteur) 
                      {
                          tab->pidAdmin = 0;
                    
                      } 
                      

                      fprintf(stderr,"(SERVEUR %d) Requete LOGOUT_ADMIN reçue de %d\n",getpid(),m.expediteur);
                      break;

      case NEW_USER : //!etape 6b

                      if (estPresent(m.data1) != 0) 
                      {
                          strcpy(m.texte, "Erreur : User existe existant");
                          strcpy(m.data1, "KO");

                      } 
                      else 
                      {
                          ajouteUtilisateur(m.data1, m.data2);
                          strcpy(m.texte, "User ajouter");

                          sprintf(requete,"INSERT INTO UNIX_FINAL VALUES (NULL,'%s','---','---')",m.data1);
                          mysql_query(connexion,requete);
                          strcpy(m.data1, "OK");
                      }

                      m.type = m.expediteur;

                      if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
                      {
                          perror("(SERVEUR) Erreur de msgsnd ->NEWW-USER");
                          exit(1);
                      }


                      fprintf(stderr,"(SERVEUR %d) Requete NEW_USER reçue de %d : --%s--%s--\n",getpid(),m.expediteur,m.data1,m.data2);
                      break;

      case DELETE_USER ://!etape 6b

                      if (estPresent(m.data1) == 0) 
                      {
                          strcpy(m.texte, "Erreur : User inexistant");
                          strcpy(m.data1, "KO");
                      } 
                      else 
                      {
                          supprimeUtilisateur(m.data1);
                          strcpy(m.texte, "User supprimer");

                          sprintf(requete, "DELETE FROM UNIX_FINAL WHERE nom='%s';", m.data1);
                          mysql_query(connexion,requete);
                          strcpy(m.data1, "OK");
                      }

                      m.type = m.expediteur;

                      if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
                      {
                          perror("(SERVEUR) Erreur de msgsnd ->DELETE-USER");
                          exit(1);
                      }

                      fprintf(stderr,"(SERVEUR %d) Requete DELETE_USER reçue de %d : --%s--\n",getpid(),m.expediteur,m.data1);
                      break;
      

      case NEW_PUB:  //!etape 6c
      
                    fdExist = (access("publicites.dat", F_OK) == 0);  

                    if ((fd = open("publicites.dat", O_WRONLY | O_APPEND | O_CREAT, 0644)) == -1) 
                    {
                        perror("(SERVEUR) Erreur open-> NEEWPUB");
                        exit(1);
                    }

                    PUBLICITE pub;
                    strcpy(pub.texte, m.texte);
                    pub.nbSecondes = atoi(m.data1);

                    if (write(fd, &pub, sizeof(PUBLICITE)) == -1) {
                        perror("(SERVEUR) Erreur write-> NEEWPUB");
                        close(fd);
                        exit(1);
                    }

                    close(fd);

                    if (!fdExist) 
                    {
                        kill(tab->pidPublicite, SIGUSR1);
                    }

                    fprintf(stderr, "(SERVEUR %d) Requête NEW_PUB traitée avec succès\n", getpid());
                    break;

    }
    afficheTab();
  }
}

void afficheTab()
{
  fprintf(stderr,"Pid Serveur 1 : %d\n",tab->pidServeur1);
  fprintf(stderr,"Pid Serveur 2 : %d\n",tab->pidServeur2);
  fprintf(stderr,"Pid Publicite : %d\n",tab->pidPublicite);
  fprintf(stderr,"Pid Admin     : %d\n",tab->pidAdmin);
  for (int i=0 ; i<6 ; i++)
    fprintf(stderr,"%6d -%20s- %6d %6d %6d %6d %6d - %6d\n",tab->connexions[i].pidFenetre,
                                                      tab->connexions[i].nom,
                                                      tab->connexions[i].autres[0],
                                                      tab->connexions[i].autres[1],
                                                      tab->connexions[i].autres[2],
                                                      tab->connexions[i].autres[3],
                                                      tab->connexions[i].autres[4],
                                                      tab->connexions[i].pidModification);
  fprintf(stderr,"\n");
}





//-----------HANDELERS ---------------

//!etape 1c
void handlerSIGINT(int sig)
{
  fprintf(stderr,"(SERVEUR) Signal sigint recu: %d",sig);

  //!etape 4
  if (shmctl(idShm, IPC_RMID, NULL) == -1) 
  {
    perror("(SERVEUR)Erreur de shmctl");
    exit(1);
  }

  if (msgctl(idQ,IPC_RMID,NULL) == -1)
  {
    perror("(serveur)Erreur de msgctl");
    exit(1);
  }

  //!etape 5c
  if (semctl(idSem, 0, IPC_RMID) == -1) 
  {  
      perror("(SERVEUR) Erreur de semctl");
  }


  kill(tab->pidPublicite,SIGINT);

  sigRecu=1;
}



void handlerSIGCHLD(int sig)
{
  int pidFils,status;

  pidFils = wait(&status);

  for(int i =0; i<6;i++)
  {
    if(tab->connexions[i].pidModification==pidFils)
    {
      tab->connexions[i].pidModification=0;
      
    }
  }
  fprintf(stderr,"(SERVEUR) Processus fils %d terminé \n",pidFils);
}