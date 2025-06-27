#include "windowadmin.h"
#include "ui_windowadmin.h"
#include <QMessageBox>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;
extern int idQ;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowAdmin::WindowAdmin(QWidget *parent):QMainWindow(parent),ui(new Ui::WindowAdmin)
{
    ui->setupUi(this);
    ::close(2);
}

WindowAdmin::~WindowAdmin()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowAdmin::setNom(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditNom->clear();
    return;
  }
  ui->lineEditNom->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowAdmin::getNom()
{
  strcpy(nom,ui->lineEditNom->text().toStdString().c_str());
  return nom;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowAdmin::setMotDePasse(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditMotDePasse->clear();
    return;
  }
  ui->lineEditMotDePasse->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowAdmin::getMotDePasse()
{
  strcpy(motDePasse,ui->lineEditMotDePasse->text().toStdString().c_str());
  return motDePasse;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowAdmin::setTexte(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditTexte->clear();
    return;
  }
  ui->lineEditTexte->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowAdmin::getTexte()
{
  strcpy(texte,ui->lineEditTexte->text().toStdString().c_str());
  return texte;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowAdmin::setNbSecondes(int n)
{
  char Text[10];
  sprintf(Text,"%d",n);
  ui->lineEditNbSecondes->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WindowAdmin::getNbSecondes()
{
  char tmp[10];
  strcpy(tmp,ui->lineEditNbSecondes->text().toStdString().c_str());
  return atoi(tmp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowAdmin::dialogueMessage(const char* titre,const char* message)
{
   QMessageBox::information(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowAdmin::dialogueErreur(const char* titre,const char* message)
{
   QMessageBox::critical(this,titre,message);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WindowAdmin::on_pushButtonAjouterUtilisateur_clicked()
{
  // TO DO
  

  //!etape 6b
    MESSAGE m;
    m.type = 1; 
    m.expediteur = getpid();
    m.requete = NEW_USER;
    strcpy(m.data1, getNom());
    strcpy(m.data2, getMotDePasse());
    

    if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
    {
      perror("(ADMIN) Erreur de msgsnd ->NEWUSER");
      exit(1);
    }

    
    if (msgrcv(idQ, &m, sizeof(MESSAGE) - sizeof(long), getpid(), 0) == -1)
    {
        perror("(ADMIN) Erreur de msgrcv -> NEWUSER");
        exit(1);
    }

    
    dialogueMessage("Ajout ", m.texte);

    setNom("");
    setMotDePasse("");

}


void WindowAdmin::on_pushButtonSupprimerUtilisateur_clicked()
{
  // TO DO
  //!etape 6b

    MESSAGE m;
    m.type = 1; 
    m.requete = DELETE_USER;
    m.expediteur = getpid();
    strcpy(m.data1, getNom());
    

    if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
    {
      perror("(ADMIN) Erreur de msgsnd ->DELETEUSER ");
      exit(1);
    }

    if (msgrcv(idQ, &m, sizeof(MESSAGE) - sizeof(long), getpid(), 0) == -1)
    {
        perror("(ADMIN) Erreur de msgrcv -> DELETEUSER");
        exit(1);
    }

    dialogueMessage("Suppression", m.texte);

    setNom("");
    setMotDePasse("");
}

void WindowAdmin::on_pushButtonAjouterPublicite_clicked()
{
  // TO DO
  //!etape 6c

  MESSAGE m;
  m.type = 1; 
  m.requete = NEW_PUB;
  m.expediteur = getpid();
  strcpy(m.texte, getTexte());
  sprintf(m.data1, "%d", getNbSecondes());

  if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
  {
    perror("(ADMIN) Erreur de msgsnd ->NEWPUB ");
    exit(1);
  }
  setTexte("");
  ui->lineEditNbSecondes->setText("");
}

void WindowAdmin::on_pushButtonQuitter_clicked()
{
  // TO DO

  //!etape 6a

  MESSAGE m;
  m.type =1; 
  m.requete = LOGOUT_ADMIN;
  m.expediteur = getpid();

  if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
  {
    perror("(ADMIN) Erreur de msgsnd ->LOGOUTADMIN");
    exit(1);
  }

  exit(0); 

}
