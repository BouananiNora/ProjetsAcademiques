#include "windowadmin.h"
#include <QApplication>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int idQ;

int main(int argc, char *argv[])
{
    // Recuperation de l'identifiant de la file de messages
    fprintf(stderr,"(ADMINISTRATEUR %d) Recuperation de l'id de la file de messages\n",getpid());

    //!etape 6a
    if ((idQ = msgget(CLE,0)) == -1)
    {
        perror("(ADMIN)Erreur de msgget");
        exit(1);
    }

    // Envoi d'une requete de connexion au serveur
    //!etape 6a

    MESSAGE m;
    m.type = 1; 
    m.requete = LOGIN_ADMIN;
    m.expediteur = getpid(); 

    if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1)
    {
        perror("(ADMIN) Erreur de msgsnd ->LOGIN_ADMIN");
        exit(1);
    }



    // Attente de la réponse
    fprintf(stderr,"(ADMINISTRATEUR %d) Attente reponse\n",getpid());

    //!etape 6a

    if (msgrcv(idQ, &m, sizeof(MESSAGE) - sizeof(long), getpid(), 0) == -1)
    {
        perror("(ADMIN) Erreur de msgrcv-> LOGIN_ADMIN");
        exit(1);
    }
    QApplication a(argc, argv);
    WindowAdmin w;

    if (strcmp(m.data1, "OK") == 0)
    {
        w.show();
        return a.exec();
    }
    else
    {
        w.dialogueErreur("Erreur", "Admin deja connecter");
        exit(0);
    }

    
}
