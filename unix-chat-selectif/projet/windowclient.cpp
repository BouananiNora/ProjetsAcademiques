#include "windowclient.h"
#include "ui_windowclient.h"
#include <QMessageBox>
#include "dialogmodification.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <signal.h>
#include <sys/shm.h>

// Definition du message pour la file de messages
extern WindowClient *w;

#include "protocole.h"

int idQ, idShm;
#define TIME_OUT 120
int timeOut = TIME_OUT;

//!etape 1a
void handlerSIGUSR1(int sig);

//!etape 3
void handlerSIGALRM(int sig);

//!etape 4

void handlerSIGUSR2(int sig);
char* pShm;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowClient::WindowClient(QWidget *parent):QMainWindow(parent),ui(new Ui::WindowClient)
{
    ui->setupUi(this);
    ::close(2);
    logoutOK();

    // Recuperation de l'identifiant de la file de messages
    fprintf(stderr,"(CLIENT %d) Recuperation de l'id de la file de messages\n",getpid());

    //!etape 1a
    if ((idQ = msgget(CLE,0)) == -1)
    {
        perror("(CLIENT)Erreur de msgget");
        exit(1);
    }

    // Recuperation de l'identifiant de la mémoire partagée
    fprintf(stderr,"(CLIENT %d) Recuperation de l'id de la mémoire partagée\n",getpid());

    //!etape 4

    
    if ((idShm = shmget(CLE, 0, 0)) == -1) 
    {
        perror("(CLIENT)Erreur de shmget");
        exit(1);
    }

    // Attachement à la mémoire partagée

    //!etape 4

    if ((pShm = (char*)shmat(idShm,NULL,0)) == (char*)-1)   //rq: pshm valeur de la zone de memoire partager
    {
      perror("(CLIENT)Erreur de shmat");
      exit(1);
    }

    // Armement des signaux

    //!etape 1a
    struct sigaction B;
    B.sa_handler = handlerSIGUSR1;
    B.sa_flags = 0;
    sigemptyset(&B.sa_mask);
    
    if(sigaction(SIGUSR1, &B, NULL)== -1)
    {
      perror("(CLIENT) Erreur de sigaction -> SIGUSR1");
      exit(1);
    }

    //!etape 3
    struct sigaction C;
    C.sa_handler = handlerSIGALRM;
    C.sa_flags = 0;
    sigemptyset(&C.sa_mask);
    
    
    if(sigaction(SIGALRM,&C,NULL)== -1)
    {
      perror("(CLIENT) Erreur de sigaction -> SIGALRM");
      exit(1);
    }

    //!etape 4

    struct sigaction D;
    D.sa_handler = handlerSIGUSR2;
    D.sa_flags = 0;
    sigemptyset(&D.sa_mask);
    
    if(sigaction(SIGUSR2, &D, NULL)== -1)
    {
      perror("(CLIENT) Erreur de sigaction -> SIGUSR2");
      exit(1);
    }

    // Envoi d'une requete de connexion au serveur
    //!etape 1a
    MESSAGE m;
    m.type=1;
    m.requete = CONNECT;
    m.expediteur = getpid();
    if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
    {
        perror("(CLIENT) Erreur de msgsnd ->CONNECT");
        exit(1);
    }
}

WindowClient::~WindowClient()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setNom(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditNom->clear();
    return;
  }
  ui->lineEditNom->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowClient::getNom()
{
  strcpy(connectes[0],ui->lineEditNom->text().toStdString().c_str());
  return connectes[0];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setMotDePasse(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditMotDePasse->clear();
    return;
  }
  ui->lineEditMotDePasse->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowClient::getMotDePasse()
{
  strcpy(motDePasse,ui->lineEditMotDePasse->text().toStdString().c_str());
  return motDePasse;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WindowClient::isNouveauChecked()
{
  if (ui->checkBoxNouveau->isChecked()) return 1;
  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setPublicite(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditPublicite->clear();
    return;
  }
  ui->lineEditPublicite->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setTimeOut(int nb)
{
  ui->lcdNumberTimeOut->display(nb);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setAEnvoyer(const char* Text)
{
  //fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditAEnvoyer->clear();
    return;
  }
  ui->lineEditAEnvoyer->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowClient::getAEnvoyer()
{
  strcpy(aEnvoyer,ui->lineEditAEnvoyer->text().toStdString().c_str());
  return aEnvoyer;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setPersonneConnectee(int i,const char* Text)
{
  if (strlen(Text) == 0 )
  {
    switch(i)
    {
        case 1 : ui->lineEditConnecte1->clear(); break;
        case 2 : ui->lineEditConnecte2->clear(); break;
        case 3 : ui->lineEditConnecte3->clear(); break;
        case 4 : ui->lineEditConnecte4->clear(); break;
        case 5 : ui->lineEditConnecte5->clear(); break;
    }
    return;
  }
  switch(i)
  {
      case 1 : ui->lineEditConnecte1->setText(Text); break;
      case 2 : ui->lineEditConnecte2->setText(Text); break;
      case 3 : ui->lineEditConnecte3->setText(Text); break;
      case 4 : ui->lineEditConnecte4->setText(Text); break;
      case 5 : ui->lineEditConnecte5->setText(Text); break;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowClient::getPersonneConnectee(int i)
{
  QLineEdit *tmp;
  switch(i)
  {
    case 1 : tmp = ui->lineEditConnecte1; break;
    case 2 : tmp = ui->lineEditConnecte2; break;
    case 3 : tmp = ui->lineEditConnecte3; break;
    case 4 : tmp = ui->lineEditConnecte4; break;
    case 5 : tmp = ui->lineEditConnecte5; break;
    default : return NULL;
  }

  strcpy(connectes[i],tmp->text().toStdString().c_str());
  return connectes[i];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::ajouteMessage(const char* personne,const char* message)
{
  // Choix de la couleur en fonction de la position
  int i=1;
  bool trouve=false;
  while (i<=5 && !trouve)
  {
      if (getPersonneConnectee(i) != NULL && strcmp(getPersonneConnectee(i),personne) == 0) trouve = true;
      else i++;
  }
  char couleur[40];
  if (trouve)
  {
      switch(i)
      {
        case 1 : strcpy(couleur,"<font color=\"red\">"); break;
        case 2 : strcpy(couleur,"<font color=\"blue\">"); break;
        case 3 : strcpy(couleur,"<font color=\"green\">"); break;
        case 4 : strcpy(couleur,"<font color=\"darkcyan\">"); break;
        case 5 : strcpy(couleur,"<font color=\"orange\">"); break;
      }
  }
  else strcpy(couleur,"<font color=\"black\">");
  if (strcmp(getNom(),personne) == 0) strcpy(couleur,"<font color=\"purple\">");

  // ajout du message dans la conversation
  char buffer[300];
  sprintf(buffer,"%s(%s)</font> %s",couleur,personne,message);
  ui->textEditConversations->append(buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setNomRenseignements(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditNomRenseignements->clear();
    return;
  }
  ui->lineEditNomRenseignements->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* WindowClient::getNomRenseignements()
{
  strcpy(nomR,ui->lineEditNomRenseignements->text().toStdString().c_str());
  return nomR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setGsm(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditGsm->clear();
    return;
  }
  ui->lineEditGsm->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setEmail(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditEmail->clear();
    return;
  }
  ui->lineEditEmail->setText(Text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setCheckbox(int i,bool b)
{
  QCheckBox *tmp;
  switch(i)
  {
    case 1 : tmp = ui->checkBox1; break;
    case 2 : tmp = ui->checkBox2; break;
    case 3 : tmp = ui->checkBox3; break;
    case 4 : tmp = ui->checkBox4; break;
    case 5 : tmp = ui->checkBox5; break;
    default : return;
  }
  tmp->setChecked(b);
  if (b) tmp->setText("Accepté");
  else tmp->setText("Refusé");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::loginOK()
{
  ui->pushButtonLogin->setEnabled(false);
  ui->pushButtonLogout->setEnabled(true);
  ui->lineEditNom->setReadOnly(true);
  ui->lineEditMotDePasse->setReadOnly(true);
  ui->checkBoxNouveau->setEnabled(false);
  ui->pushButtonEnvoyer->setEnabled(true);
  ui->pushButtonConsulter->setEnabled(true);
  ui->pushButtonModifier->setEnabled(true);
  ui->checkBox1->setEnabled(true);
  ui->checkBox2->setEnabled(true);
  ui->checkBox3->setEnabled(true);
  ui->checkBox4->setEnabled(true);
  ui->checkBox5->setEnabled(true);
  ui->lineEditAEnvoyer->setEnabled(true);
  ui->lineEditNomRenseignements->setEnabled(true);
  setTimeOut(TIME_OUT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::logoutOK()
{
  ui->pushButtonLogin->setEnabled(true);
  ui->pushButtonLogout->setEnabled(false);
  ui->lineEditNom->setReadOnly(false);
  ui->lineEditNom->setText("");
  ui->lineEditMotDePasse->setReadOnly(false);
  ui->lineEditMotDePasse->setText("");
  ui->checkBoxNouveau->setEnabled(true);
  ui->pushButtonEnvoyer->setEnabled(false);
  ui->pushButtonConsulter->setEnabled(false);
  ui->pushButtonModifier->setEnabled(false);
  for (int i=1 ; i<=5 ; i++)
  {
      setCheckbox(i,false);
      setPersonneConnectee(i,"");
  }
  ui->checkBox1->setEnabled(false);
  ui->checkBox2->setEnabled(false);
  ui->checkBox3->setEnabled(false);
  ui->checkBox4->setEnabled(false);
  ui->checkBox5->setEnabled(false);
  setNomRenseignements("");
  setGsm("");
  setEmail("");
  ui->textEditConversations->clear();
  setAEnvoyer("");
  ui->lineEditAEnvoyer->setEnabled(false);
  ui->lineEditNomRenseignements->setEnabled(false);
  setTimeOut(TIME_OUT);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::dialogueMessage(const char* titre,const char* message)
{
   QMessageBox::information(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::dialogueErreur(const char* titre,const char* message)
{
   QMessageBox::critical(this,titre,message);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Clic sur la croix de la fenêtre ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::closeEvent(QCloseEvent *event)
{
    // TO DO
    //!etape 1a

    MESSAGE m;
    m.type=1;
    m.requete = LOGOUT;
    m.expediteur = getpid();

    if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
    {
        perror("(CLIENT) Erreur de msgsnd ->LOGOUT");
    }

    m.requete = DECONNECT;

    if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1) 
    {
        perror("(CLIENT) Erreur de msgsnd ->DECONNECT");
    }

    QApplication::exit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::on_pushButtonLogin_clicked()
{
    // TO DO

    //!etape 1b
    MESSAGE m;

  if(strcmp(getNom(),"")!=0 && strcmp(getMotDePasse(),"")!=0)
  {
    m.type=1;
    m.requete = LOGIN;
    m.expediteur = getpid();

    if(isNouveauChecked())
    {
      strcpy(m.data1, "1");
    }
    else
    {
      strcpy(m.data1, "0");
    }

    
    strcpy(m.data2, getNom()); 
    strcpy(m.texte, getMotDePasse()); 

    m.requete = LOGIN;
    
    if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1)
    {
        perror("(CLIENT) Erreur de msgsnd-> LOGIN");
        return;
    }
  }
  else
  {
    dialogueErreur("Erreur", "Login/Mdp vides");
  }

}

void WindowClient::on_pushButtonLogout_clicked()
{
    // TO DO

    //!etape 1b
    MESSAGE m;
    m.type=1;   //rq:NE PAS OUBLIER TYPE =1
    m.requete = LOGOUT;
    m.expediteur = getpid(); 
    strcpy(m.data1, getNom());


    if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1)
    {
        perror("(CLIENT) Erreur de msgsnd->LOGOUT");
        exit(0);
    }
    
    logoutOK();

    //!etape3

    alarm(0);
    timeOut=TIME_OUT;
}

void WindowClient::on_pushButtonEnvoyer_clicked()
{
    // TO DO

    //!etape3

    alarm(0);
    timeOut=TIME_OUT;
    alarm(1);

   
    //!etape 2c

    MESSAGE m;
    m.type=1;
    m.requete = SEND;
    m.expediteur = getpid();
    const char* message = getAEnvoyer();
    strcpy(m.texte, message);

    if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1)
    {
        perror("(CLIENT) Erreur de msgsnd->SEND");
        exit(1);
    }
    setAEnvoyer("");    //nb:effacer la barre de msg 
}

void WindowClient::on_pushButtonConsulter_clicked()
{
    // TO DO

    //!etape3

    alarm(0);
    timeOut=TIME_OUT;
    alarm(1);

    //!etape 5a

    MESSAGE m;
    m.type=1;
    m.requete = CONSULT;
    m.expediteur = getpid();

    if(strcmp(getNomRenseignements(),"")!=0)
    {
      strcpy(m.data1, getNomRenseignements());

      if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1)
      {
          perror("(CLIENT) Erreur de msgsnd -> CONSULT");
          exit(1);
      }
    }
    else
    {
      dialogueErreur("Erreur","Nom est vide"); 
    } 

}

void WindowClient::on_pushButtonModifier_clicked()
{
  // TO DO

    //!etape3

    alarm(0);
    timeOut=TIME_OUT;
    alarm(1);


  // Envoi d'une requete MODIF1 au serveur
  MESSAGE m;
  // ...
  //!etape 5b

  m.type = 1;
  m.requete = MODIF1;
  m.expediteur = getpid();
  strcpy(m.data1, getNom());

  if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1)
  {
      perror("(CLIENT) Erreur de msgsnd -> MODIF1");
      exit(1);
  }

  // Attente d'une reponse en provenance de Modification
  fprintf(stderr,"(CLIENT %d) Attente reponse MODIF1\n",getpid());
  // ...
  //!etape 5b
  
  if (msgrcv(idQ, &m, sizeof(MESSAGE) - sizeof(long), getpid(), 0) == -1)
  {
      perror("(CLIENT) Erreur de msgrcv -> MODIF1");
      exit(1);
  }

  // Verification si la modification est possible
  if (strcmp(m.data1,"KO") == 0 && strcmp(m.data2,"KO") == 0 && strcmp(m.texte,"KO") == 0)
  {
    QMessageBox::critical(w,"Problème...","Modification déjà en cours...");
    return;
  }

  // Modification des données par utilisateur
  DialogModification dialogue(this,getNom(),"",m.data2,m.texte);
  dialogue.exec();
  char motDePasse[40];
  char gsm[40];
  char email[40];
  strcpy(motDePasse,dialogue.getMotDePasse());
  strcpy(gsm,dialogue.getGsm());
  strcpy(email,dialogue.getEmail());

  // Envoi des données modifiées au serveur
  // ...
  //!etape 5b
  m.type=1;
  m.requete = MODIF2;
  strcpy(m.data1, motDePasse);
  strcpy(m.data2, gsm);
  strcpy(m.texte, email);

  if (msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1)
  {
      perror("(CLIENT) Erreur de msgsnd -> MODIF2");
      exit(1);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les checkbox ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::on_checkBox1_clicked(bool checked)
{

    //!etape3

    alarm(0);
    timeOut=TIME_OUT;
    alarm(1);

   
  //!etape 2b

  MESSAGE m;
  m.type=1;
  m.expediteur = getpid();
  strcpy(m.data1, getPersonneConnectee(1));

    if (checked)
    {
        ui->checkBox1->setText("Accepté");
        // TO DO (etape 2)

        m.requete = ACCEPT_USER;

        if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
        {
          perror("(CLIENT) Erreur de msgsnd -> ACCEPT_USER");
        }
    }
    else
    {
        ui->checkBox1->setText("Refusé");
        // TO DO (etape 2)

        m.requete = REFUSE_USER;

        if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
        {
          perror("(CLIENT) Erreur de msgsnd -> ACCEPT_USER");
        }
    }
}

void WindowClient::on_checkBox2_clicked(bool checked)
{

    //!etape3

    alarm(0);
    timeOut=TIME_OUT;
    alarm(1);

   
  //!etape 2b

  MESSAGE m;
  m.type=1;
  m.expediteur = getpid();
  strcpy(m.data1, getPersonneConnectee(2));

    if (checked)
    {
        ui->checkBox2->setText("Accepté");
        // TO DO (etape 2)

        m.requete = ACCEPT_USER;

        if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
        {
          perror("(CLIENT) Erreur de msgsnd -> ACCEPT_USER");
        }
    }
    else
    {
        ui->checkBox2->setText("Refusé");
        // TO DO (etape 2)

        m.requete = REFUSE_USER;

        if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
        {
          perror("(CLIENT) Erreur de msgsnd -> ACCEPT_USER");
        }
    }
}

void WindowClient::on_checkBox3_clicked(bool checked)
{

    //!etape3

    alarm(0);
    timeOut=TIME_OUT;
    alarm(1);

   
    //!etape 2b

  MESSAGE m;
  m.type=1;
  m.expediteur = getpid();
  strcpy(m.data1, getPersonneConnectee(3));

    if (checked)
    {
        ui->checkBox3->setText("Accepté");
        // TO DO (etape 2)

        m.requete = ACCEPT_USER;

        if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
        {
          perror("(CLIENT) Erreur de msgsnd -> ACCEPT_USER");
        }
    }
    else
    {
        ui->checkBox3->setText("Refusé");
        // TO DO (etape 2)

        m.requete = REFUSE_USER;

        if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
        {
          perror("(CLIENT) Erreur de msgsnd -> ACCEPT_USER");
        }
    }
}

void WindowClient::on_checkBox4_clicked(bool checked)
{

    //!etape3

    alarm(0);
    timeOut=TIME_OUT;
    alarm(1);

   
    //!etape 2b

  MESSAGE m;
  m.type=1;
  m.expediteur = getpid();
  strcpy(m.data1, getPersonneConnectee(4));

    if (checked)
    {
        ui->checkBox4->setText("Accepté");
        // TO DO (etape 2)

        m.requete = ACCEPT_USER;

        if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
        {
          perror("(CLIENT) Erreur de msgsnd -> ACCEPT_USER");
        }
    }
    else
    {
        ui->checkBox4->setText("Refusé");
        // TO DO (etape 2)

        m.requete = REFUSE_USER;

        if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
        {
          perror("(CLIENT) Erreur de msgsnd -> ACCEPT_USER");
        }
    }
}

void WindowClient::on_checkBox5_clicked(bool checked)
{

    //!etape3

    alarm(0);
    timeOut=TIME_OUT;
    alarm(1);

   
    //!etape 2b

  MESSAGE m;
  m.type=1;
  m.expediteur = getpid();
  strcpy(m.data1, getPersonneConnectee(5));

    if (checked)
    {
        ui->checkBox5->setText("Accepté");
        // TO DO (etape 2)

        m.requete = ACCEPT_USER;

        if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
        {
          perror("(CLIENT) Erreur de msgsnd -> ACCEPT_USER");
        }
    }
    else
    {
        ui->checkBox5->setText("Refusé");
        // TO DO (etape 2)

        m.requete = REFUSE_USER;

        if(msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0) == -1)
        {
          perror("(CLIENT) Erreur de msgsnd -> ACCEPT_USER");
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handlers de signaux ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void handlerSIGUSR1(int sig)
{
    MESSAGE m;
    
    // ...msgrcv(idQ,&m,...)

    //!etape 1b
    //!etape 2b 
    //rq: (etape2b)ajout de while pour gerer pls msg enovyer (login,adduser)
    while (msgrcv(idQ, &m, sizeof(MESSAGE) - sizeof(long), getpid(), IPC_NOWAIT) != -1)   //rq: IPCNOWAIT permet de ne plus rester bloquer qui est causer par msgrcv
    {
    
      switch(m.requete)
      {
        case LOGIN :
                    if (strcmp(m.data1,"OK") == 0)
                    {
                      fprintf(stderr,"(CLIENT %d) Login OK\n",getpid());
                      w->loginOK();
                      w->dialogueMessage("Login...",m.texte);
                      // ...

                      //!etape 3

                      timeOut=TIME_OUT;
                      alarm(1);

                    }
                    else w->dialogueErreur("Login...",m.texte);
                    break;

        case ADD_USER :
                    // TO DO

                    //!etape 2a

                    for (int i=1; i<=5; i++) 
                    {
                        if (strcmp(w->getPersonneConnectee(i), "")== 0) 
                        {
                            w->setPersonneConnectee(i,m.data1);
                            break;
                        }
                    }
                    
                    break;

        case REMOVE_USER :
                    // TO DO

                    //!etape 2a

                    for (int i=1; i<=5; i++) 
                    {
                        if (strcmp(w->getPersonneConnectee(i), m.data1)== 0) 
                        {
                            w->setPersonneConnectee(i,""); 
                            break;
                        }
                    }

                    break;

        case SEND :
                    // TO DO

                    //!etape 2c

                    w->ajouteMessage(m.data1, m.texte);

                    break;

        case CONSULT :
                  // TO DO

                  //!etape 5a

                  if(strcmp(m.data1,"OK")==0)
                  {
                    w->setGsm(m.data2);
                    w->setEmail(m.texte);
                  }
                  else
                  {
                    
                    w->setGsm("NON TROUVE");
                    w->setEmail("NON TROUVE");
                  }
                  break;
      }
    }
}



//!etape 3
void handlerSIGALRM(int sig)
{
  fprintf(stderr,"(CLIENT) Reception du signal SIGALRM (%d)\n",sig);

  
  if(timeOut>0)       //nb: tant que le temps nest pas a 0,on decremente le temps
  {
    timeOut--;
    w->setTimeOut(timeOut);
    alarm(1);
  }
  else      //nb:sinon (temps=0),on est delogge
  {
    fprintf(stderr,"(CLIENT) timer a 0");
    w->on_pushButtonLogout_clicked();
  }

  
}

//!etape 4
void handlerSIGUSR2(int sig)
{
  fprintf(stderr,"(CLIENT) Reception du signal SIGUSR2 (%d)\n",sig);

    if (pShm) 
    {
        w->setPublicite(pShm);
    }
}