#include "Couleur.h"
using namespace std;
#include <iostream>

//------------------constructeur------------------

Couleur::Couleur()                      //par defaut
{
    #ifdef DEBUG
          cout<<"(Couleur)  Constructeur par defaut "<<endl;
    #endif

    rouge=0;
    vert=0;
    bleu=0;
}

Couleur::Couleur(int rouge, int vert ,int bleu)          //initialisation
{
    #ifdef DEBUG
          cout<<"(Couleur)  Constructeur d'initialisation "<<endl;
    #endif

    setRouge(rouge);
    setVert(vert);
    setBleu(bleu);
}

Couleur::Couleur(const Couleur& clr)          //de copie
{
    #ifdef DEBUG
        cout<<"(Couleur)  Constructeur par de copie"<<endl;
    #endif

    setRouge(clr.getRouge());
    setVert(clr.getVert());
    setBleu(clr.getBleu());

}

//------------------destructeur------------------

 Couleur::~Couleur()
  {
    #ifdef DEBUG
          cout<<"(Couleur)  Destructeur "<<endl;
    #endif
  }

//------------------objet------------------

 Couleur Couleur::ROUGE(255, 0, 0);
 Couleur Couleur::VERT(0, 255, 0);
 Couleur Couleur::BLEU(0, 0, 255);
 Couleur Couleur::BLANC(255, 255, 255);
 Couleur Couleur::NOIR(0, 0, 0);


//------------------getter------------------

int Couleur::getRouge() const 
{
    return rouge;
}

int Couleur::getVert() const 
{
    return vert;
}

int Couleur::getBleu() const 
{
    return bleu;
}

//------------------setter------------------

void Couleur::setRouge(int r) 
{
    if (r >= 0 && r <= 255) 
    {
        rouge = r;
    }
}

void Couleur::setVert(int v) 
{
    if  (v >= 0 && v <= 255 )
    {
        vert = v;
    }
}

void Couleur::setBleu(int b) 
{
    if (b >= 0 && b <= 255)
    {
        bleu = b;
    }
}

//------------------surcharge------------------

ostream& operator<<(ostream& s,const Couleur& clr)
{
    s << clr.getRouge() << "/" << clr.getVert() << "/" << clr.getBleu();
    return s;
}


Couleur& Couleur::operator=(const Couleur& clr)
  {
    setRouge(clr.getRouge());
    setVert(clr.getVert());
    setBleu(clr.getBleu());
    
    return (*this);
    
  }

//------------------methodes------------------

  void Couleur::Affiche()       //maj avvec dimension
  {
    cout << "Rouge: " << rouge << endl;
    cout << "Vert: " << vert << endl;
        cout << "Bleu: " << bleu << endl;

  }