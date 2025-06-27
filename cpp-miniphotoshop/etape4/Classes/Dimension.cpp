#include "Dimension.h"
using namespace std;
#include <iostream>

//------------------methodes(private)------------------

int Dimension::compDim(const Dimension&dim)
{
    if(largeur!=dim.largeur) return -1;
    if(hauteur!=dim.hauteur)  return -1;
    // if(largeur==dim.largeur) return 0;
    // if(hauteur==dim.hauteur)  return 0;
return 0;
}

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

//------------------surcharge------------------

ostream& operator<<(ostream& s,const Dimension& d)
{
    s << d.getLargeur() << "/" << d.getHauteur();
    return s;
}

istream& operator>>(istream& s, Dimension& d)
{
    int largeur, hauteur;
    char x='/';

    s >> largeur >> x >> hauteur;

    if (largeur > 0 && hauteur > 0) 
    {
        d.setLargeur(largeur);
        d.setHauteur(hauteur);
    }

    return s;
}

int Dimension::operator==(const Dimension &dim)
{
    return compDim(dim)==0;
}

int Dimension::operator!=(const Dimension &dim)
{
    return compDim(dim)==-1;
}



