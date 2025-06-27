#include "FichierUtilisateur.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>


int estPresent(const char* nom)
{
  // TO DO

  int fd,i;
  UTILISATEUR user;

  if((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) == -1)  
  {
    return -1;
  }

  for(i=1;read(fd,&user,sizeof(UTILISATEUR)) == sizeof(UTILISATEUR) ;i++)
  {
    if(strcmp(user.nom,nom)==0)
    {
      close(fd);
      return i;
    }
  }

  if(close(fd)==-1)
  {
    perror("Erreur de close()");
    exit(1);
  }
  return 0;

}

////////////////////////////////////////////////////////////////////////////////////
int hash(const char* motDePasse)
{
  // TO DO
  const char *p=motDePasse;
  int somme,i;

  for(i=1,somme=0;*p!='\0';p++,i++)
  {
    somme+=i*(int)*p;
  }
  somme=somme%97;

  return somme;
}

////////////////////////////////////////////////////////////////////////////////////
void ajouteUtilisateur(const char* nom, const char* motDePasse)
{
  // TO DO
  int fd;
  UTILISATEUR user;

  if((fd = open(FICHIER_UTILISATEURS, O_WRONLY | O_CREAT | O_APPEND,0644)) == -1) //rq:metre les flags a 0644 pour que tout le monde puisse lire et que le proprio puisse ecrire
  {                                                                               //rq: append->Ecriture en fin de fichier
    perror("Erreur de open()");
    exit(1);
  }

  strcpy(user.nom, nom);
  user.hash = hash(motDePasse);

  if (write(fd, &user, sizeof(UTILISATEUR)) == -1)
  {
      perror("Erreur lors de l'écriture dans le fichier");
      close(fd);
      exit(1);  
  }

  if(close(fd)==-1)
  {
    perror("Erreur de close()");
    exit(1);
  }

}

////////////////////////////////////////////////////////////////////////////////////
int verifieMotDePasse(int pos, const char* motDePasse)
{
  // TO DO
  int fd,mdp;
  UTILISATEUR user;

  if((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) == -1)
  {
    perror("Erreur de open()");
    exit(1);
  }

  lseek(fd,(pos-1)*sizeof(UTILISATEUR),SEEK_SET);

  if(read(fd,&user,sizeof(UTILISATEUR))!= sizeof(UTILISATEUR))
  {
    perror("Erreur lecture fichier");
    close(fd);
    return 0;
  }

  mdp = hash(motDePasse);

  if(mdp == user.hash) 
  {
    return 1;
  }
  else 
    return 0;

  
}

////////////////////////////////////////////////////////////////////////////////////
int listeUtilisateurs(UTILISATEUR *vecteur) // le vecteur doit etre suffisamment grand
{
  // TO DO
  int fd,i;
  UTILISATEUR user;

  if((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) == -1)
  {
    perror("Erreur de open()");
    exit(1);
  }

  for(i=0;read(fd,&user,sizeof(UTILISATEUR)) == sizeof(UTILISATEUR) ;i++,vecteur++)
  {
    *vecteur=user;
  }

  if(close(fd)==-1)
  {
    perror("Erreur de close()");
    exit(1);
  }
  return i;

}

////////////////////////////////////////////////////////////////////////////////////

//!etape 5b
int modifMotDePasse(char* nom, char* motDePasse)
{
  
  int fd;
  UTILISATEUR user;

  if((fd = open(FICHIER_UTILISATEURS, O_RDWR)) == -1)  
  {
    return -1;
  }

  while(read(fd,&user,sizeof(UTILISATEUR)) == sizeof(UTILISATEUR))
  {
    if(strcmp(nom,user.nom) == 0)
    {
      user.hash = hash(motDePasse);

      lseek(fd, -1*sizeof(UTILISATEUR), SEEK_CUR);

      write(fd, &user, sizeof(UTILISATEUR)) ;

      close(fd);

      return 1;
    }
  }

  close(fd);
  return 1;

}


//!etape 6b
int supprimeUtilisateur(char* nom)
{
    int fd, fdTemp;
    UTILISATEUR user;
    char temp[] = "temp.dat";

    if ((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) == -1) 
    {
        perror("Erreur ouverture fichier fd");
        return -1;
    }

    if ((fdTemp = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) //rq: trunc->Détruit le contenu du fichier s’il existe déjà
    {
        perror("Erreur ouverture fichier fd");
        close(fd);
        return -1;
    }

    while (read(fd, &user, sizeof(UTILISATEUR)) == sizeof(UTILISATEUR)) //nb: on ecrit dans le fichier temp les nom differents du nom a supprimer 
    {
        if (strcmp(user.nom, nom) != 0) //nb: tant qu'un nom est different du nom a supprimer ,on ecrit dans le fichier
        {
            write(fdTemp, &user, sizeof(UTILISATEUR));
        }
    }

    close(fd);
    close(fdTemp);

    remove(FICHIER_UTILISATEURS);
    rename(temp, FICHIER_UTILISATEURS);

    return 1;
}
