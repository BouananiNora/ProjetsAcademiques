#include "Dimension.h"
using namespace std;
#include <iostream>

//------------------constructeur------------------

Dimension::Dimension()                      //par defaut
{
    #ifdef DEBUG
          cout<<"(Dimension)  Constructeur par defaut "<<endl;
    #endif

    largeur=400; 
    hauteur=300;
}

Dimension::Dimension(int l, int h)          //initialisation
{
    #ifdef DEBUG
          cout<<"(Dimension)  Constructeur d'initialisation "<<endl;
    #endif

    setLargeur(l);
    setHauteur(h);
}

Dimension::Dimension(const Dimension& dim)          //de copie
{
    #ifdef DEBUG
        cout<<"(Dimension)  Constructeur par de copie"<<endl;
    #endif

    setLargeur(dim.getLargeur());
    setHauteur(dim.getHauteur());
}

//------------------destructeur------------------

 Dimension::~Dimension()
  {
    #ifdef DEBUG
          cout<<"(Dimension)  Destructeur "<<endl;
    #endif
  }

//------------------objet------------------

const Dimension Dimension::VGA(640, 480);

const Dimension Dimension::HD(1280, 720);

const Dimension Dimension::FULL_HD(1920, 1080);

//------------------methodes------------------

void Dimension::Affiche() const
{
    cout << "Largeur = " << largeur << ", Hauteur = " << hauteur << endl;
}

//------------------getter------------------

int Dimension::getLargeur() const 
{
    return largeur;
}

int Dimension::getHauteur() const 
{
    return hauteur;
}

//------------------setter------------------

void Dimension::setLargeur(int l) 
{
    if (l > 0) 
    {
        largeur = l;
    }
}

void Dimension::setHauteur(int h) 
{
    if (h > 0) 
    {
        hauteur = h;
    }
}

