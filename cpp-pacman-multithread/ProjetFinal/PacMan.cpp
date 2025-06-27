#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "GrilleSDL.h"
#include "Ressources.h"

// Dimensions de la grille de jeu
#define NB_LIGNE 21
#define NB_COLONNE 17

// Macros utilisees dans le tableau tab
#define VIDE         0
#define MUR          1
#define PACMAN       2
#define PACGOM       3
#define SUPERPACGOM  4
#define BONUS        5
#define FANTOME      6

// Autres macros
#define LENTREE 15
#define CENTREE 8

typedef struct
{
  int L;
  int C;
  int couleur;
  int cache;
} S_FANTOME;

typedef struct {
  int presence;
  pthread_t tid;
} S_CASE;



//-------------------------------------------------------------------------
//-------------------------Variables globales-------------------------
//-------------------------------------------------------------------------

S_CASE tab[NB_LIGNE][NB_COLONNE];

// ETAPE 1
pthread_mutex_t mutexTab;  
int L = LENTREE;  // lig init a 15
int C = CENTREE;  // col init a 8
int dir = GAUCHE; // dir init a guache
pthread_t threadPacMan; 
// ETAPE 1---

// ETAPE 2
  pthread_t threadEvent;
// ETAPE 2---

// ETAPE 3
pthread_t threadPacGom;
pthread_mutex_t mutexNbPacGom;
pthread_cond_t condNbPacGom;
int nbPacGom = 0;  // Nombre de pac-goms dans la grille
int delai = 300;   // Délai en ms (0,3 sec initialement)
pthread_mutex_t mutexDelai;  // Pour protéger la variable delai
// ETAPE 3---

// ETAPE 4
pthread_t threadScore;       // Thread pour gérer le score
pthread_mutex_t mutexScore;  // Mutex pour protéger le score
pthread_cond_t condScore;    // Variable de condition pour le score
int score = 0;               // Score actuel du jeu
bool MAJScore = false; 
// ETAPE 4---

// ETAPE 5
pthread_t threadBonus;  // Thread pour le bonus
// ETAPE 5---

// ETAPE 6
pthread_t threadCompteurFantomes;  // Thread compteur de fantômes
pthread_mutex_t mutexNbFantomes;   // Mutex pour protéger le nombre de fantômes
pthread_cond_t condNbFantomes;     // Variable de condition pour le nombre de fantômes
int nbRouge = 0;  // Nombre de fantômes rouges
int nbVert = 0;   // Nombre de fantômes verts
int nbMauve = 0;  // Nombre de fantômes mauves
int nbOrange = 0; // Nombre de fantômes oranges
int mode = 1;     // Mode du jeu: 1 = fantômes gloutons, 2 = fantômes comestibles
pthread_key_t fantomeKey;  // Clé pour accéder aux données spécifiques au thread fantôme
// ETAPE 6---

// ETAPE 7
pthread_t threadVies;       // Thread pour gérer les vies
int nbVies = 3;             // Nombre de vies initial
pthread_mutex_t mutexVies;  // Mutex pour protéger le nombre de vies
bool gameOver = false;      // Indicateur de fin de partie
// ETAPE 7---

// ETAPE 8
pthread_t threadTimeOut = 0;  // Thread pour gérer le timeout du mode comestible
pthread_mutex_t mutexMode;    // Mutex pour protéger la variable mode
pthread_cond_t condMode;      // Variable de condition pour le mode
bool gameRunning = true;
// ETAPE 8---



//-------------------------------------------------------------------------
//-------------------------Prototypes de fonctions-------------------------
//-------------------------------------------------------------------------

void DessineGrilleBase();
void Attente(int milli);
void setTab(int l, int c, int presence = VIDE, pthread_t tid = 0);

// ETAPE 1
void* threadPacManFct(void* arg);
// ETAPE 1---

// ETAPE 2
void* threadEventFct(void* arg);
void handlerSIGINT(int sig);
void handlerSIGHUP(int sig);
void handlerSIGUSR1(int sig);
void handlerSIGUSR2(int sig);
// ETAPE 2---

// ETAPE 3
void remplirGrillePacGoms();
void* threadPacGomFct(void* arg);
// ETAPE 3---

// ETAPE 4
void majScore(int points);
void* threadScoreFct(void* arg);
// ETAPE 4---

// ETAPE 5
void* threadBonusFct(void* arg);
// ETAPE 5---

// ETAPE 6
void* threadCompteurFantomesFct(void* arg);
void* threadFantomeFct(void* arg);
// ETAPE 6---

// ETAPE 7
void* threadViesFct(void* arg);
// ETAPE 7---

// ETAPE 8
void fantomeCleanupHandler(void* arg);
void* threadTimeOutFct(void* arg);
void handlerSIGALRM(int sig);
void handlerSIGCHLD(int sig);
void handlerSIGQUIT(int sig);
// ETAPE 8---

///////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc,char* argv[])
{
  EVENT_GRILLE_SDL event;
  sigset_t mask;
  struct sigaction sigAct;
  char ok;

  srand((unsigned)time(NULL));

  // Ouverture de la fenetre graphique
  printf("(MAIN%p) Ouverture de la fenetre graphique\n",pthread_self()); fflush(stdout);
  if (OuvertureFenetreGraphique() < 0)
  {
    printf("Erreur de OuvrirGrilleSDL\n");
    fflush(stdout);
    exit(1);
  }


  // ETAPE 1
  pthread_mutex_init(&mutexTab, NULL);
  // ETAPE 1---

  // ETAPE 3
  pthread_mutex_init(&mutexNbPacGom, NULL);
  pthread_cond_init(&condNbPacGom, NULL);
  pthread_mutex_init(&mutexDelai, NULL);
  // ETAPE 3---

  // ETAPE 4
  pthread_mutex_init(&mutexScore, NULL);
  pthread_cond_init(&condScore, NULL);
  // ETAPE 4---

  // ETAPE 6
  pthread_mutex_init(&mutexNbFantomes, NULL);
  pthread_cond_init(&condNbFantomes, NULL);
  pthread_key_create(&fantomeKey, NULL);  // Création de la clé pour les données spécifiques aux threads fantômes
  // ETAPE 6---

  // ETAPE 7
  pthread_mutex_init(&mutexVies, NULL);
  // ETAPE 7---

  // ETAPE 8 
  pthread_mutex_init(&mutexMode, NULL);
  pthread_cond_init(&condMode, NULL);
  // ETAPE 8---

  DessineGrilleBase();

  // ETAPE 2
  // Armement des signaux pour changer la direction de Pac-Man
  sigAct.sa_handler = handlerSIGINT;  // Gauche
  sigemptyset(&sigAct.sa_mask);
  sigAct.sa_flags = 0;
  sigaction(SIGINT, &sigAct, NULL);

  sigAct.sa_handler = handlerSIGHUP;  // Droite
  sigemptyset(&sigAct.sa_mask);
  sigAct.sa_flags = 0;
  sigaction(SIGHUP, &sigAct, NULL);

  sigAct.sa_handler = handlerSIGUSR1; // Haut
  sigemptyset(&sigAct.sa_mask);
  sigAct.sa_flags = 0;
  sigaction(SIGUSR1, &sigAct, NULL);

  sigAct.sa_handler = handlerSIGUSR2; // Bas
  sigemptyset(&sigAct.sa_mask);
  sigAct.sa_flags = 0;
  sigaction(SIGUSR2, &sigAct, NULL);
  // ETAPE 2---

  // ETAPE 8
  sigAct.sa_handler = handlerSIGALRM;  // Fin du mode fantômes comestibles
  sigemptyset(&sigAct.sa_mask);
  sigAct.sa_flags = 0;
  sigaction(SIGALRM, &sigAct, NULL);

  sigAct.sa_handler = handlerSIGCHLD;  // Fantôme mangé par Pac-Man
  sigemptyset(&sigAct.sa_mask);
  sigAct.sa_flags = 0;
  sigaction(SIGCHLD, &sigAct, NULL);

  sigAct.sa_handler = handlerSIGQUIT;  // Annulation d'un TimeOut en cours
  sigemptyset(&sigAct.sa_mask);
  sigAct.sa_flags = 0;
  sigaction(SIGQUIT, &sigAct, NULL);
  // ETAPE 8---

  // ETAPE 3
  printf("Création du thread PacGom...\n");
  pthread_create(&threadPacGom, NULL, threadPacGomFct, NULL);
  // ETAPE 3---

  // ETAPE 4
  printf("Création du thread Score...\n");
  pthread_create(&threadScore, NULL, threadScoreFct, NULL);
  // ETAPE 4---

  // ETAPE 5
  printf("Création du thread Bonus...\n");
  pthread_create(&threadBonus, NULL, threadBonusFct, NULL);
  // ETAPE 5---

  // ETAPE 6
  printf("Création du thread CompteurFantomes...\n");
  pthread_create(&threadCompteurFantomes, NULL, threadCompteurFantomesFct, NULL);
  // ETAPE 6---

  // // ETAPE 1
  // printf("Création du thread Pac-Man...\n");
  // pthread_create(&threadPacMan, NULL, threadPacManFct, NULL);
  // // ETAPE 1---

  // ETAPE 7
  // Au lieu de créer directement threadPacMan, on crée threadVies
  printf("Création du thread Vies...\n");
  pthread_create(&threadVies, NULL, threadViesFct, NULL);
  // ETAPE 7---

  // ETAPE 2
  printf("Création du thread Event...\n");
  pthread_create(&threadEvent, NULL, threadEventFct, NULL);
  
  // On attend la fin du thread Event (et non plus Pac-Man)
  pthread_join(threadEvent, NULL);
  // ETAPE 2---

  // ETAPE 1
  pthread_mutex_destroy(&mutexTab);
  // ETAPE 1---

  // ETAPE 3
  pthread_mutex_destroy(&mutexNbPacGom);
  pthread_cond_destroy(&condNbPacGom);
  pthread_mutex_destroy(&mutexDelai);
  // ETAPE 3---

  // ETAPE 4
  pthread_mutex_destroy(&mutexScore);
  pthread_cond_destroy(&condScore);
  // ETAPE 4---

  // ETAPE 6
  pthread_mutex_destroy(&mutexNbFantomes);
  pthread_cond_destroy(&condNbFantomes);
  pthread_key_delete(fantomeKey);
  // ETAPE 6---

  // ETAPE 7
  pthread_mutex_destroy(&mutexVies);
  // ETAPE 7---

  // ETAPE 8
  pthread_mutex_destroy(&mutexMode);
  pthread_cond_destroy(&condMode);
  // ETAPE 8---

  // -------------------------------------------------------------------------
  
  // Fermeture de la fenetre
  printf("(MAIN %p) Fermeture de la fenetre graphique...",pthread_self()); 
  fflush(stdout);
  FermetureFenetreGraphique();
  printf("OK\n"); 
  fflush(stdout);

  exit(0);
}

//*********************************************************************************************
void Attente(int milli) {
  struct timespec del;
  del.tv_sec = milli/1000;
  del.tv_nsec = (milli%1000)*1000000;
  nanosleep(&del,NULL);
}

//*********************************************************************************************
void setTab(int l, int c, int presence, pthread_t tid) {
  tab[l][c].presence = presence;
  tab[l][c].tid = tid;
}

//*********************************************************************************************
void DessineGrilleBase() {
  int t[NB_LIGNE][NB_COLONNE]
    = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
        {1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0,1},
        {1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,1},
        {1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1},
        {1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,1,1},
        {1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1},
        {0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0},
        {1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,1},
        {1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,1,1},
        {1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,1},
        {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
        {1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1},
        {1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1},
        {1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1},
        {1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,1},
        {1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  for (int l=0 ; l<NB_LIGNE ; l++)
    for (int c=0 ; c<NB_COLONNE ; c++) {
      if (t[l][c] == VIDE) {
        setTab(l,c);
        EffaceCarre(l,c);
      }
      if (t[l][c] == MUR) {
        setTab(l,c,MUR); 
        DessineMur(l,c);
      }
    }
}

//*********************************************************************************************
// ETAPE 3
// Fonction séparée pour remplir la grille avec des pac-goms
void remplirGrillePacGoms()
{
  pthread_mutex_lock(&mutexTab);
  
  // Réinitialisation du compteur de pac-goms
  pthread_mutex_lock(&mutexNbPacGom);
  nbPacGom = 0;
  pthread_mutex_unlock(&mutexNbPacGom);
  
  // Parcours de la grille pour placer les pac-goms
  for (int l = 0; l < NB_LIGNE; l++)
  {
    for (int c = 0; c < NB_COLONNE; c++)
    {
      // Ignorer les cases contenant des murs
      if (tab[l][c].presence == MUR)
        continue;
        
      // Ignorer la case de départ de Pac-Man
      if (l == LENTREE && c == CENTREE)
        continue;
        
      // Ignorer le "futur nid" des fantômes
      if ((l == 8 && c == 8) || (l == 9 && c == 8))
        continue;
        
      // Cas spéciaux: placer 4 super pac-goms aux coins
      if ((l == 2 && c == 1) || (l == 2 && c == 15) || 
          (l == 15 && c == 1) || (l == 15 && c == 15))
      {
        setTab(l, c, SUPERPACGOM);
        DessineSuperPacGom(l, c);
        
        pthread_mutex_lock(&mutexNbPacGom);
        nbPacGom++;
        pthread_mutex_unlock(&mutexNbPacGom);
      }
      // Remplir les autres cases libres avec des pac-goms normaux
      else if (tab[l][c].presence == VIDE)
      {
        setTab(l, c, PACGOM);
        DessinePacGom(l, c);
        
        pthread_mutex_lock(&mutexNbPacGom);
        nbPacGom++;
        pthread_mutex_unlock(&mutexNbPacGom);
      }
    }
  }
  
  pthread_mutex_unlock(&mutexTab);
  
  // Affichage du nombre de pac-goms
  DessineChiffre(12, 22, nbPacGom / 100);  // Centaines
  DessineChiffre(12, 23, (nbPacGom % 100) / 10);  // Dizaines
  DessineChiffre(12, 24, nbPacGom % 10);  // Unités
}
// ETAPE 3---

//*********************************************************************************************
// ETAPE 4
void majScore(int points) {
    pthread_mutex_lock(&mutexScore);
    score += points;
    MAJScore = true;
    pthread_cond_signal(&condScore);
    pthread_mutex_unlock(&mutexScore);
}
// ETAPE 4---

//*********************************************************************************************

// ETAPE 8
// Fonction de nettoyage pour les fantômes mangés par Pac-Man
void fantomeCleanupHandler(void* arg) 
{
    S_FANTOME* fantome = (S_FANTOME*)pthread_getspecific(fantomeKey);
    
    if (fantome != NULL)
    {
        printf("(ThreadFantome %p) Nettoyage: Fantôme mangé par Pac-Man\n", pthread_self());
        
        // Libérer la case du fantôme dans la grille
        pthread_mutex_lock(&mutexTab);
        setTab(fantome->L, fantome->C);
        EffaceCarre(fantome->L, fantome->C);
        pthread_mutex_unlock(&mutexTab);
        
        // Augmenter le score de 50 points pour avoir mangé un fantôme
        pthread_mutex_lock(&mutexScore);
        score += 50;
        
        // Ajouter des points supplémentaires selon ce qui était caché sous le fantôme
        if (fantome->cache == PACGOM)
        {
            score += 1;
            
            // Décrémenter le nombre de pac-goms
            pthread_mutex_lock(&mutexNbPacGom);
            nbPacGom--;
            pthread_cond_signal(&condNbPacGom);
            pthread_mutex_unlock(&mutexNbPacGom);
        }
        else if (fantome->cache == SUPERPACGOM)
        {
            score += 5;
            
            // Décrémenter le nombre de pac-goms
            pthread_mutex_lock(&mutexNbPacGom);
            nbPacGom--;
            pthread_cond_signal(&condNbPacGom);
            pthread_mutex_unlock(&mutexNbPacGom);
        }
        else if (fantome->cache == BONUS)
        {
            score += 30;
        }
        
        // Signaler la mise à jour du score
        MAJScore = true;
        pthread_cond_signal(&condScore);
        pthread_mutex_unlock(&mutexScore);
        
        // Décrémenter le compteur de fantôme correspondant
        pthread_mutex_lock(&mutexNbFantomes);
        switch (fantome->couleur)
        {
            case ROUGE:  nbRouge--;  break;
            case VERT:   nbVert--;   break;
            case MAUVE:  nbMauve--;  break;
            case ORANGE: nbOrange--; break;
        }
        
        // Réveiller le thread compteur de fantômes
        pthread_cond_signal(&condNbFantomes);
        pthread_mutex_unlock(&mutexNbFantomes);
        
        // Libérer la mémoire allouée pour la structure du fantôme
        free(fantome);
    }
}

//*********************************************************************************************


//--------------------------------------------------------------------
//-------------------------THREADS------------------------------------
//--------------------------------------------------------------------

// ETAPE 7
// Thread qui gère les vies de Pac-Man
void* threadViesFct(void* arg)
{
  printf("(ThreadVies %p) Démarrage\n", pthread_self());
  
  // Affiche le nombre de vies initial à la case (18,22)
  DessineChiffre(18, 22, nbVies);
  
  // Boucle principale qui lance 3 threads Pac-Man séquentiellement
  while(nbVies > 0 && !gameOver)
  {
    // Réinitialisation de la position et direction de Pac-Man
    L = LENTREE;
    C = CENTREE;
    dir = GAUCHE;
    
    printf("(ThreadVies) Lancement de Pac-Man, vies restantes: %d\n", nbVies);
    
    // Création du thread Pac-Man
    pthread_create(&threadPacMan, NULL, threadPacManFct, NULL);
    
    // Attendre la fin du thread Pac-Man (quand il est mangé par un fantôme)
    pthread_join(threadPacMan, NULL);
    
    // Décrémenter le nombre de vies
    pthread_mutex_lock(&mutexVies);
    nbVies--;
    pthread_mutex_unlock(&mutexVies);
    
    // Mise à jour de l'affichage du nombre de vies
    DessineChiffre(18, 22, nbVies);
    
    // Attente d'une seconde avant de relancer un nouveau Pac-Man
    Attente(1000);
  }
  
  // Afficher "Game Over" quand toutes les vies sont épuisées
  if(nbVies == 0)
  {
    /// Marquer la partie comme terminée
    pthread_mutex_lock(&mutexVies);
    gameOver = true;
    pthread_mutex_unlock(&mutexVies);
    
    // Arrêter tous les threads sauf Event qui est nécessaire pour fermer l'application
    if(threadBonus != 0)
        pthread_cancel(threadBonus);
    if(threadScore != 0)
        pthread_cancel(threadScore);
    if(threadPacGom != 0)
        pthread_cancel(threadPacGom);
    if(threadCompteurFantomes != 0)
        pthread_cancel(threadCompteurFantomes);
    if(threadTimeOut != 0)
        pthread_cancel(threadTimeOut);
    
    // Attendre un instant pour que tous les threads s'arrêtent
    Attente(500);
    
    // Dessiner le message Game Over par-dessus tout le reste
    DessineGameOver(9, 4);
    
    printf("(ThreadVies) GAME OVER - Plus de vies!\n");
    
    // Les threads fantômes se termineront d'eux-mêmes car ils vérifient gameOver dans leur boucle
  }
  
  return NULL;
}
// ETAPE 7---


// ETAPE 1
//gere deplacement de pacman dans la grille
void* threadPacManFct(void* arg)
{
  int nouvL, nouvC;// rq:stock nvl coordonnes: nouvelle lignes et colonnes
  // ETAPE 2
  sigset_t mask;
  // ETAPE 2---

  // ETAPE 3
  int delaiActuel;
  // ETAPE 3---

  printf("(ThreadPacMan %p) Démarrage\n", pthread_self());
  
  // ETAPE 7
  //Routine de nettoyage pour effacer Pac-Man de la grille
  pthread_cleanup_push(
    [](void* arg) {
      pthread_mutex_lock(&mutexTab);
      // Effacer Pac-Man de sa position actuelle
      setTab(L, C);
      EffaceCarre(L, C);
      pthread_mutex_unlock(&mutexTab);
      printf("(ThreadPacMan %p) Nettoyage et fin\n", pthread_self());
    },
    NULL
  );
  // ETAPE 7---

  // ETAPE 2
  // Masque des signaux pour Pac-Man
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);  // Gauche
  sigaddset(&mask, SIGHUP);  // Droite
  sigaddset(&mask, SIGUSR1); // Haut
  sigaddset(&mask, SIGUSR2); // Bas
  // ETAPE 2---

  // Placement initial de Pac-Man sur la grille
  pthread_mutex_lock(&mutexTab);//rq:Verrouille mutex pour avoir un acces a tab
  setTab(L, C, PACMAN, pthread_self());//rq:maj tab a la position (L,C) ou pacman sy trouve avec lid du thread
  DessinePacMan(L, C, dir);//rq:affiche pacam a cette position avec la direction specifier
  pthread_mutex_unlock(&mutexTab);//rq:deveroille mutex tab
  
  
  while(1)
  {
    // ETAPE 3
    // On lit le délai actuel (protégé par un mutex)
    pthread_mutex_lock(&mutexDelai);
    delaiActuel = delai;
    pthread_mutex_unlock(&mutexDelai);
    // ETAPE 3---
    
    // ETAPE 2
    // Section critique 1: bloquer les signaux pendant l'attente
    pthread_sigmask(SIG_BLOCK, &mask, NULL); // Utiliser pthread_sigmask au lieu de sigprocmask
    // ETAPE 2---
    
    Attente(delaiActuel); // On utilise le délai actuel au lieu de 300 ms
    
    // ETAPE 2
    // Fin de section critique 1: permettre la réception des signaux
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);
    // ETAPE 2---
    
    // copie position actuelle
    nouvL = L;
    nouvC = C;
    
    switch(dir)
    {
      case HAUT:    nouvL--; break;
      case BAS:     nouvL++; break;
      case GAUCHE:  nouvC--; break;
      case DROITE:  nouvC++; break;
    }
    
    // ETAPE 2
    // Section critique 2: bloquer les signaux pendant la mise à jour de la grille
    pthread_sigmask(SIG_BLOCK, &mask, NULL);
    // ETAPE 2---

    pthread_mutex_lock(&mutexTab);
    
    if (nouvL >= 0 && nouvL < NB_LIGNE && nouvC >= 0 && nouvC < NB_COLONNE && 
        tab[nouvL][nouvC].presence != MUR)
    {
      // ETAPE 8
      // Vérifier si Pac-Man rencontre un fantôme
      if (tab[nouvL][nouvC].presence == FANTOME)
      {
        pthread_mutex_lock(&mutexMode);
        int modeActuel = mode;
        pthread_mutex_unlock(&mutexMode);
        
        if (modeActuel == 1)  // Mode fantômes gloutons - Pac-Man meurt
        {
          printf("(ThreadPacMan %p) Collision avec un fantôme! Pac-Man meurt...\n", pthread_self());
          pthread_mutex_unlock(&mutexTab); // Important: débloquer le mutex avant de terminer!
          pthread_sigmask(SIG_UNBLOCK, &mask, NULL); // Débloquer les signaux avant de terminer
          pthread_exit(NULL);
        }
        else  // Mode fantômes comestibles - Pac-Man mange le fantôme
        {
          printf("(ThreadPacMan) Miam! Un fantôme comestible!\n");
          
          // Récupérer le tid du fantôme
          pthread_t tidFantome = tab[nouvL][nouvC].tid;
          
          // Envoyer un signal au fantôme pour qu'il se termine
          pthread_kill(tidFantome, SIGCHLD);
          
          // Effacer l'ancienne position de Pac-Man
          setTab(L, C);
          EffaceCarre(L, C);
          
          // Mise à jour de la position de Pac-Man
          L = nouvL;
          C = nouvC;
          
          // Redessiner Pac-Man à sa nouvelle position
          setTab(L, C, PACMAN, pthread_self());
          DessinePacMan(L, C, dir);
        }
      }
      // ETAPE 8---

      // ETAPE 3
      // Vérifie si Pac-Man va manger un pac-gom ou un super pac-gom
      else if (tab[nouvL][nouvC].presence == PACGOM)
      {
        // ETAPE 4
        // Mise à jour du score (+1 point pour un pac-gom normal)
        majScore(1);
        // ETAPE 4---

        // Décrémente le nombre de pac-goms
        pthread_mutex_lock(&mutexNbPacGom);
        nbPacGom--;
        pthread_cond_signal(&condNbPacGom); // Signal immédiatement après la modification
        pthread_mutex_unlock(&mutexNbPacGom);
        
        // Effacer l'ancienne position
        setTab(L, C);
        EffaceCarre(L, C);
        
        // Mise à jour des coordonnées
        L = nouvL;
        C = nouvC;
        
        // Redessiner à la nouvelle position
        setTab(L, C, PACMAN, pthread_self());
        DessinePacMan(L, C, dir);
      }
      else if (tab[nouvL][nouvC].presence == SUPERPACGOM)
      {
        // ETAPE 4
        // Mise à jour du score (+5 points pour un super pac-gom)
        majScore(5);
        // ETAPE 4---

        // Décrémente le nombre de pac-goms
        pthread_mutex_lock(&mutexNbPacGom);
        nbPacGom--;
        pthread_cond_signal(&condNbPacGom); // Signal immédiatement après la modification
        pthread_mutex_unlock(&mutexNbPacGom);

        // ETAPE 8
        // Passer en mode "Fantômes comestibles"
        pthread_mutex_lock(&mutexMode);
        mode = 2;  // Mode fantômes comestibles
        pthread_cond_signal(&condMode);  // Réveiller le threadCompteurFantomes

        // Gestion du threadTimeOut - vous pouvez utiliser mutexMode pour protéger threadTimeOut
        pthread_t oldTimeOut = threadTimeOut;
        int secondesRestantes = 0;

        if (oldTimeOut != 0)
        {
            // Annuler l'alarme précédente et récupérer le temps restant
            secondesRestantes = alarm(0);
            
            // Terminer le thread TimeOut précédent
            pthread_kill(oldTimeOut, SIGQUIT);
            
            }

        // Créer un nouveau thread TimeOut
        int* tempsTotal = (int*)malloc(sizeof(int));
        *tempsTotal = secondesRestantes;  // Temps restant du précédent timeout

        pthread_create(&threadTimeOut, NULL, threadTimeOutFct, (void*)tempsTotal);
        pthread_detach(threadTimeOut); // Détacher pour éviter les fuites de ressources
        
        pthread_mutex_unlock(&mutexMode);
        // ETAPE 8---
        
        // Effacer l'ancienne position
        setTab(L, C);
        EffaceCarre(L, C);
        
        // Mise à jour des coordonnées
        L = nouvL;
        C = nouvC;
        
        // Redessiner à la nouvelle position
        setTab(L, C, PACMAN, pthread_self());
        DessinePacMan(L, C, dir);
      }
      // ETAPE 5
      else if (tab[nouvL][nouvC].presence == BONUS)
      {
        // Mise à jour du score (+30 points pour un bonus)
        majScore(30);
        
        printf("(ThreadPacMan) Bonus mangé! +30 points\n");
        
        // Effacer l'ancienne position
        setTab(L, C);
        EffaceCarre(L, C);
        
        // Mise à jour des coordonnées
        L = nouvL;
        C = nouvC;
        
        // Redessiner à la nouvelle position
        setTab(L, C, PACMAN, pthread_self());
        DessinePacMan(L, C, dir);
      }
      // ETAPE 5---
      else // Case vide ou autre
      {
        // Effacer l'ancienne position
        setTab(L, C);
        EffaceCarre(L, C);
        
        // Mise à jour des coordonnées
        L = nouvL;
        C = nouvC;
        
        // Redessiner à la nouvelle position
        setTab(L, C, PACMAN, pthread_self());
        DessinePacMan(L, C, dir);
      }
    }
    
    pthread_mutex_unlock(&mutexTab);

    // ETAPE 2
    // Fin de section critique 2: permettre la réception des signaux
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);
    // ETAPE 2---
  }
  
  // ETAPE 7
  // Exécuter et annuler la routine de nettoyage
  pthread_cleanup_pop(1);
  // ETAPE 7---

  return NULL;
}
// ETAPE 1---


// ETAPE 2
//gere event d'interface (clavier, souris, croix)
void* threadEventFct(void* arg)
{
  EVENT_GRILLE_SDL event;
  sigset_t mask;
  
  printf("(ThreadEvent %p) Démarrage\n", pthread_self());
  
  // Masque tous les signaux pour ce thread
  sigfillset(&mask);
  pthread_sigmask(SIG_SETMASK, &mask, NULL);
  char ok;
  ok = 0;
  while(!ok)
  {
    event = ReadEvent();
    if (event.type == CROIX) 
    {
      ok = 1;
      printf("Fermeture de la fenêtre demandée\n");
      exit(0);
    }
    
    if (event.type == CLAVIER)
    {
      switch(event.touche)
      {
        case KEY_LEFT:
          printf("Touche gauche appuyée, envoi signal SIGINT à PacMan\n");
          pthread_kill(threadPacMan, SIGINT); // Envoie signal pour aller à gauche
          break;
          
        case KEY_RIGHT:
          printf("Touche droite appuyée, envoi signal SIGHUP à PacMan\n");
          pthread_kill(threadPacMan, SIGHUP); // Envoie signal pour aller à droite
          break;
          
        case KEY_UP:
          printf("Touche haut appuyée, envoi signal SIGUSR1 à PacMan\n");
          pthread_kill(threadPacMan, SIGUSR1); // Envoie signal pour aller en haut
          break;
          
        case KEY_DOWN:
          printf("Touche bas appuyée, envoi signal SIGUSR2 à PacMan\n");
          pthread_kill(threadPacMan, SIGUSR2); // Envoie signal pour aller en bas
          break;
          
        default:
          printf("Touche non gérée: %c\n", event.touche);
          break;
      }
    }
  }
  pthread_exit(NULL);
  
}
// ETAPE 2---


// ETAPE 3
// Thread qui remplit la grille de pac-goms et gère le niveau
void* threadPacGomFct(void* arg)
{
  int niveau = 1;  // Niveau initial du jeu
  
  printf("(ThreadPacGom %p) Démarrage\n", pthread_self());
  
  // Remplir la grille initialement
  remplirGrillePacGoms();
  
  // Boucle principale du thread
  while(1)
  {
    // Attendre que tous les pac-goms soient mangés
    pthread_mutex_lock(&mutexNbPacGom);
    while (nbPacGom > 0)
    {
      pthread_cond_wait(&condNbPacGom, &mutexNbPacGom);
      
      // Mise à jour de l'affichage du nombre de pac-goms
      DessineChiffre(12, 22, nbPacGom / 100);  // Centaines
      DessineChiffre(12, 23, (nbPacGom % 100) / 10);  // Dizaines
      DessineChiffre(12, 24, nbPacGom % 10);  // Unités
    }
    pthread_mutex_unlock(&mutexNbPacGom);
    
    // Tous les pac-goms ont été mangés, passage au niveau suivant
    niveau++;
    
    // Affichage du niveau
    DessineChiffre(14, 22, niveau);
    
    // Accélération du jeu (division par 2 du délai)
    pthread_mutex_lock(&mutexDelai);
    delai /= 2;
    pthread_mutex_unlock(&mutexDelai);
    
    // Remplir à nouveau la grille de pac-goms
    remplirGrillePacGoms();
  }
  
  return NULL;
}
// ETAPE 3---


// ETAPE 4
// Thread qui gère l'affichage du score
void* threadScoreFct(void* arg)
{
  printf("(ThreadScore %p) Démarrage\n", pthread_self());
  
  // Initialiser l'affichage du score à zéro
  DessineChiffre(16, 22, 0);  // Milliers
  DessineChiffre(16, 23, 0);  // Centaines
  DessineChiffre(16, 24, 0);  // Dizaines
  DessineChiffre(16, 25, 0);  // Unités
  
  // Boucle principale du thread
  while(1)
  {
    // Attendre que le score soit mis à jour
    pthread_mutex_lock(&mutexScore);
    while (MAJScore == false)
    {
      pthread_cond_wait(&condScore, &mutexScore);
    }
    
    // Mise à jour de l'affichage du score
    DessineChiffre(16, 22, score / 1000);          // Milliers
    DessineChiffre(16, 23, (score % 1000) / 100);  // Centaines
    DessineChiffre(16, 24, (score % 100) / 10);    // Dizaines
    DessineChiffre(16, 25, score % 10);            // Unités
    
    // Réinitialiser l'indicateur de mise à jour du score
    MAJScore = false;
    pthread_mutex_unlock(&mutexScore);
  }
  
  return NULL;
}
// ETAPE 4---

 
// ETAPE 5
// Thread qui gère l'apparition aléatoire du bonus
void* threadBonusFct(void* arg)
{
  int bonusL, bonusC;
  int delaiApparition, positions_libres;
  int casesLibres[NB_LIGNE * NB_COLONNE][2];  // Tableau pour stocker les coordonnées des cases libres
  
  printf("(ThreadBonus %p) Démarrage\n", pthread_self());
  
  while(1)
  {
    // Attente aléatoire entre 10 et 20 secondes avant d'afficher un bonus
    delaiApparition = (rand() % 11) + 10;  // Nombre aléatoire entre 10 et 20
    printf("(ThreadBonus) Attente de %d secondes avant prochain bonus\n", delaiApparition);
    Attente(delaiApparition * 1000);  // Conversion en millisecondes
    
    // Recherche d'une case libre dans la grille
    pthread_mutex_lock(&mutexTab);
    
    // Compter les cases libres
    positions_libres = 0;
    for(int l = 0; l < NB_LIGNE; l++)
    {
      for(int c = 0; c < NB_COLONNE; c++)
      {
        if(tab[l][c].presence == VIDE)
        {
          casesLibres[positions_libres][0] = l;
          casesLibres[positions_libres][1] = c;
          positions_libres++;
        }
      }
    }
    
    // S'il y a des cases libres, en choisir une au hasard
    if(positions_libres > 0)
    {
      int idx = rand() % positions_libres;
      bonusL = casesLibres[idx][0];
      bonusC = casesLibres[idx][1];
      
      // Placer le bonus
      setTab(bonusL, bonusC, BONUS);
      DessineBonus(bonusL, bonusC);
      printf("(ThreadBonus) Bonus placé en (%d,%d)\n", bonusL, bonusC);
      pthread_mutex_unlock(&mutexTab);
      
      // Attendre 10 secondes
      Attente(10000);
      
      // Vérifier si le bonus est toujours présent
      pthread_mutex_lock(&mutexTab);
      if(tab[bonusL][bonusC].presence == BONUS)
      {
        // Le bonus n'a pas été mangé, l'effacer
        setTab(bonusL, bonusC, VIDE);
        EffaceCarre(bonusL, bonusC);
        printf("(ThreadBonus) Bonus en (%d,%d) disparu\n", bonusL, bonusC);
      }
    }
    
    pthread_mutex_unlock(&mutexTab);
  }
  
  return NULL;
}
// ETAPE 5---


// ETAPE 6
void* threadCompteurFantomesFct(void* arg)
{
  printf("(ThreadCompteurFantomes %p) Démarrage\n", pthread_self());
  
  // On attend que tous les compteurs soient à 2 pour chaque couleur
  while(1)
  {
    pthread_mutex_lock(&mutexNbFantomes);
    
    // On attend que le nombre de fantômes soit insuffisant
    while(nbRouge == 2 && nbVert == 2 && nbMauve == 2 && nbOrange == 2)
    {
      printf("(ThreadCompteurFantomes) Nombre de fantômes complet, attente...\n");
      pthread_cond_wait(&condNbFantomes, &mutexNbFantomes);
    }
    pthread_mutex_unlock(&mutexNbFantomes);
    
    // ETAPE 8
    // Mode fantômes comestibles - on attend que le mode revienne à 1
    pthread_mutex_lock(&mutexMode);
    if(mode == 2)
    {
      printf("(ThreadCompteurFantomes) Mode fantômes comestibles, attente...\n");
      while(mode == 2)
      {
        pthread_cond_wait(&condMode, &mutexMode);
      }
    }
    pthread_mutex_unlock(&mutexMode);
    // ETAPE 8---
    
    pthread_mutex_lock(&mutexNbFantomes);
    
    // Déterminer la couleur du fantôme à créer
    int couleur;
    if(nbRouge < 2)
      couleur = ROUGE;
    else if(nbVert < 2)
      couleur = VERT;
    else if(nbMauve < 2)
      couleur = MAUVE;
    else
      couleur = ORANGE;
    
    pthread_mutex_unlock(&mutexNbFantomes);
    
    // Création d'un nouveau fantôme
    S_FANTOME* nouveau = (S_FANTOME*)malloc(sizeof(S_FANTOME));
    nouveau->L = 9;             // Position initiale: nid des fantômes
    nouveau->C = 8;
    nouveau->couleur = couleur;
    nouveau->cache = VIDE;      // Rien sous le fantôme au départ
    
    // Mise à jour du compteur correspondant
    pthread_mutex_lock(&mutexNbFantomes);
    switch(couleur)
    {
      case ROUGE:  nbRouge++;  break;
      case VERT:   nbVert++;   break;
      case MAUVE:  nbMauve++;  break;
      case ORANGE: nbOrange++; break;
    }
    pthread_mutex_unlock(&mutexNbFantomes);
    
    printf("(ThreadCompteurFantomes) Création d'un fantôme %d (%d,%d,%d,%d)\n", 
           couleur, nbRouge, nbVert, nbMauve, nbOrange);
    
    // Création du thread fantôme
    pthread_t tid;
    pthread_create(&tid, NULL, threadFantomeFct, (void*)nouveau);
  }
  
  return NULL;
}
// ETAPE 6---


// ETAPE 6
void* threadFantomeFct(void* arg)
{
  S_FANTOME* fantome = (S_FANTOME*)arg;
  int nouvL, nouvC;
  int dir = HAUT;  // Direction initiale du fantôme
  
  // Création d'un masque pour n'accepter que SIGCHLD
sigset_t mask;
sigfillset(&mask);
sigdelset(&mask, SIGCHLD);  // Accepter uniquement SIGCHLD
pthread_sigmask(SIG_SETMASK, &mask, NULL);  // Utiliser pthread_sigmask pour les threads

// Enregistrement des données spécifiques du thread
pthread_setspecific(fantomeKey, fantome);
  
  printf("(ThreadFantome %p) Démarrage fantôme couleur %d en (%d,%d)\n", pthread_self(), fantome->couleur, fantome->L, fantome->C);
  
  // ETAPE 7
  // Routine de nettoyage pour libérer la mémoire lorsque le thread se termine
  // pthread_cleanup_push(
  //   [](void* arg) {
  //     Libérer la mémoire allouée pour la structure S_FANTOME
  //     S_FANTOME* fantome = (S_FANTOME*)pthread_getspecific(fantomeKey);
  //     if(fantome != NULL) {
  //       free(fantome);
  //     }
  //   }, 
  //   NULL
  // );
  // ETAPE 7---

  // ETAPE 8
  // Routine de nettoyage pour quand le fantôme est mangé
  // Pour l'étape 8 (nettoyage quand mangé par Pac-Man)
  pthread_cleanup_push(fantomeCleanupHandler, NULL);
  // ETAPE 8---

  // Placement initial du fantôme sur la grille
  pthread_mutex_lock(&mutexTab);
  
  // Vérifier qu'aucun autre fantôme n'est déjà sur cette case
  while(tab[fantome->L][fantome->C].presence == FANTOME)
  {
    pthread_mutex_unlock(&mutexTab);
    Attente(100);  // Attendre un peu avant de réessayer
    pthread_mutex_lock(&mutexTab);
  }
  
  // Mémoriser ce qui se trouve sous le fantôme
  fantome->cache = tab[fantome->L][fantome->C].presence;
  
  // Placer le fantôme
  setTab(fantome->L, fantome->C, FANTOME, pthread_self());
  
  // Dessiner le fantôme selon sa couleur et sa direction
   pthread_mutex_lock(&mutexMode);
  if(mode == 1)  // Mode fantômes gloutons
    DessineFantome(fantome->L, fantome->C, fantome->couleur, dir);
  else  // Mode fantômes comestibles
    DessineFantomeComestible(fantome->L, fantome->C);
  pthread_mutex_unlock(&mutexMode);
  
  pthread_mutex_unlock(&mutexTab);
  
  // Boucle principale du fantôme
  while(1)
  { 
    // ETAPE 7
    //Vérifier si la partie est terminée (game over)
    pthread_mutex_lock(&mutexVies);
    if(gameOver)
    {
      pthread_mutex_unlock(&mutexVies);
      break;  // Sortir de la boucle si game over
    }
    pthread_mutex_unlock(&mutexVies);
    // ETAPE 7---

    // Lire le délai actuel et calculer le délai du fantôme (5/3 du délai de Pac-Man)
    pthread_mutex_lock(&mutexDelai);
    int delaiFantome = (delai * 5) / 3;
    pthread_mutex_unlock(&mutexDelai);
    
    // Attendre avant le prochain déplacement
    Attente(delaiFantome);
    
    // Déterminer la nouvelle position selon la direction
    nouvL = fantome->L;
    nouvC = fantome->C;
    
    switch(dir)
    {
      case HAUT:    nouvL--; break;
      case BAS:     nouvL++; break;
      case GAUCHE:  nouvC--; break;
      case DROITE:  nouvC++; break;
    }
    
    pthread_mutex_lock(&mutexTab);
    
    // Vérifier si le déplacement est possible (pas de mur ni d'autre fantôme)
    if(nouvL >= 0 && nouvL < NB_LIGNE && nouvC >= 0 && nouvC < NB_COLONNE && 
       tab[nouvL][nouvC].presence != MUR && tab[nouvL][nouvC].presence != FANTOME)
    {
      // Si le fantôme rencontre Pac-Man
      if(tab[nouvL][nouvC].presence == PACMAN)
      {
        if(mode == 1)  // Mode fantômes gloutons - Pac-Man meurt
        {
          printf("(ThreadFantome %p) Pac-Man touché! Game over...\n", pthread_self());
          pthread_cancel(threadPacMan);

          // Considérer que la case est maintenant VIDE et non PACMAN
          tab[nouvL][nouvC].presence = VIDE;
          tab[nouvL][nouvC].tid = 0;
        }
        else  // Mode fantômes comestibles - Changer de direction
        {
          // ETAPE 8
          // Trouver une autre direction possible
          pthread_mutex_unlock(&mutexTab);
          
          // Changement de direction aléatoire
          int directions[4];
          int nbDirections = 0;
          
          // Vérifier les directions possibles
          if(fantome->L > 0 && tab[fantome->L-1][fantome->C].presence != MUR && 
             tab[fantome->L-1][fantome->C].presence != FANTOME && tab[fantome->L-1][fantome->C].presence != PACMAN)
            directions[nbDirections++] = HAUT;
          
          if(fantome->L < NB_LIGNE-1 && tab[fantome->L+1][fantome->C].presence != MUR && 
             tab[fantome->L+1][fantome->C].presence != FANTOME && tab[fantome->L+1][fantome->C].presence != PACMAN)
            directions[nbDirections++] = BAS;
          
          if(fantome->C > 0 && tab[fantome->L][fantome->C-1].presence != MUR && 
             tab[fantome->L][fantome->C-1].presence != FANTOME && tab[fantome->L][fantome->C-1].presence != PACMAN)
            directions[nbDirections++] = GAUCHE;
          
          if(fantome->C < NB_COLONNE-1 && tab[fantome->L][fantome->C+1].presence != MUR && 
             tab[fantome->L][fantome->C+1].presence != FANTOME && tab[fantome->L][fantome->C+1].presence != PACMAN)
            directions[nbDirections++] = DROITE;
          
          
          
          if(nbDirections > 0)
            dir = directions[rand() % nbDirections];
          
          pthread_mutex_unlock(&mutexTab);

          continue;  // Refaire un tour de boucle
          // ETAPE 8---
        }
      }
      
      // Restaurer ce qui était caché sous le fantôme
      setTab(fantome->L, fantome->C, fantome->cache);
      if(fantome->cache == VIDE)
        EffaceCarre(fantome->L, fantome->C);
      else if(fantome->cache == PACGOM)
        DessinePacGom(fantome->L, fantome->C);
      else if(fantome->cache == SUPERPACGOM)
        DessineSuperPacGom(fantome->L, fantome->C);
      else if(fantome->cache == BONUS)
        DessineBonus(fantome->L, fantome->C);
      
      // Mise à jour de la position
      fantome->L = nouvL;
      fantome->C = nouvC;
      
      // Mémoriser ce qui est caché sous le fantôme à sa nouvelle position
      fantome->cache = tab[fantome->L][fantome->C].presence;
      
      // Placer le fantôme à sa nouvelle position
      setTab(fantome->L, fantome->C, FANTOME, pthread_self());
      
      // ETAPE 8
      // Dessiner le fantôme selon le mode actuel
      pthread_mutex_lock(&mutexMode);
      int modeActuel = mode;
      pthread_mutex_unlock(&mutexMode);
      
      if(modeActuel == 1)  // Mode fantômes gloutons
        DessineFantome(fantome->L, fantome->C, fantome->couleur, dir);
      else  // Mode fantômes comestibles
        DessineFantomeComestible(fantome->L, fantome->C);
      // ETAPE 8---
    }
    else  // Déplacement impossible, changer de direction
    {
      // Trouver une autre direction possible
      int directions[4];
      int nbDirections = 0;
      
      // Vérifier les directions possibles
      if(fantome->L > 0 && tab[fantome->L-1][fantome->C].presence != MUR && 
         tab[fantome->L-1][fantome->C].presence != FANTOME)
        directions[nbDirections++] = HAUT;
      
      if(fantome->L < NB_LIGNE-1 && tab[fantome->L+1][fantome->C].presence != MUR && 
         tab[fantome->L+1][fantome->C].presence != FANTOME)
        directions[nbDirections++] = BAS;
      
      if(fantome->C > 0 && tab[fantome->L][fantome->C-1].presence != MUR && 
         tab[fantome->L][fantome->C-1].presence != FANTOME)
        directions[nbDirections++] = GAUCHE;
      
      if(fantome->C < NB_COLONNE-1 && tab[fantome->L][fantome->C+1].presence != MUR && 
         tab[fantome->L][fantome->C+1].presence != FANTOME)
        directions[nbDirections++] = DROITE;
      
      if(nbDirections > 0)
        dir = directions[rand() % nbDirections];
    }
    
    pthread_mutex_unlock(&mutexTab);
  }
  // ETAPE 8
  pthread_cleanup_pop(1);// Exécuter fantomeCleanupHandler
  // ETAPE 8---

  return NULL;
}
// ETAPE 6---


// ETAPE 8
// Thread TimeOut qui gère la durée du mode "Fantômes comestibles"
void* threadTimeOutFct(void* arg) 
{
    int* tempsRestantPtr = (int*)arg;
    int tempsTotal = *tempsRestantPtr + (rand() % 8 + 8);  // 8-15 secondes + temps restant
    
    free(tempsRestantPtr);  // Libération immédiate de l'argument

    // Masquer tous les signaux sauf SIGALRM/SIGQUIT
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGALRM);
    sigdelset(&mask, SIGQUIT);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);

    alarm(tempsTotal);  // Programmer l'alarme

    pause();  // Attendre SIGALRM ou SIGQUIT

    
    return NULL;
}
// ETAPE 8---


//--------------------------------------------------------------------
//-------------------------HANDLERS-----------------------------------
//--------------------------------------------------------------------

// ETAPE 2
void handlerSIGINT(int sig)
{
  dir = GAUCHE;
  printf("Direction changée: GAUCHE\n");
}
// ETAPE 2---


// ETAPE 2
void handlerSIGHUP(int sig)
{
  dir = DROITE;
  printf("Direction changée: DROITE\n");
}
// ETAPE 2---


// ETAPE 2
void handlerSIGUSR1(int sig)
{
  dir = HAUT;
  printf("Direction changée: HAUT\n");
}
// ETAPE 2---


// ETAPE 2
void handlerSIGUSR2(int sig)
{
  dir = BAS;
  printf("Direction changée: BAS\n");
}
// ETAPE 2---


// ETAPE 8 
// Handler pour SIGALRM - Fin du mode fantômes comestibles
void handlerSIGALRM(int sig)
{
  printf("(HandlerSIGALRM) Fin du mode fantômes comestibles\n");
  // Si on arrive ici, c'est soit par SIGALRM soit par SIGQUIT
    // Pour SIGALRM, on doit explicitement modifier le mode, comme demandé dans la consigne
    pthread_mutex_lock(&mutexMode);
    mode = 1;  // Retour au mode fantômes gloutons
    pthread_cond_signal(&condMode);  // Réveiller threadCompteurFantomes
    threadTimeOut = 0;  // Indiquer qu'il n'y a plus de TimeOut actif
    pthread_mutex_unlock(&mutexMode);

}
// ETAPE 8---


// ETAPE 8 
// Handler pour SIGCHLD - Fantôme mangé par Pac-Man
void handlerSIGCHLD(int sig)
{
  // Ce handler est très simple: il termine juste le thread fantôme
  // La routine de nettoyage s'occupera du reste
  pthread_exit(NULL);
}
// ETAPE 8---


// ETAPE 8 
// Handler pour SIGQUIT - Annulation d'un TimeOut en cours
void handlerSIGQUIT(int sig)
{
  printf("(HandlerSIGQUIT) Annulation du TimeOut en cours\n");
  
  // Terminer le thread TimeOut
  pthread_exit(NULL);
}
// ETAPE 8---
