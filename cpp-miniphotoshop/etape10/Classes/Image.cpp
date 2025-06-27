

#include "MyQT.h"
#include "string.h"
#include "Image.h"
using namespace std;
#include <iostream>
#include <fstream>


//------------------constructeur------------------

Image::Image()                    //par defaut
{
    #ifdef DEBUG
        cout<<"(Image)  Constructeur par defaut "<<endl;
    #endif

    nom = "Inconnu";
    id=1;
}

Image::Image(int i, const string &n)   //initialisation
{
#ifdef DEBUG
        cout<<"(Image)  Constructeur d'initialisation "<<endl;
#endif

setNom(n);
setId(i);

}

Image::Image(int i, const string &n, const Dimension& dim)   //initialisation avec dimension
{
#ifdef DEBUG
        cout<<"(Image)  Constructeur d'initialisation avec dimension"<<endl;
#endif

    setNom(n);
    setId(i);
    setDimension(dim); 

}

Image::Image(const Image &img)
{
    #ifdef DEBUG
        cout<<"(Image)  Constructeur par de copie"<<endl;
    #endif
    
    setNom(img.getNom());
    setId(img.getId());
    setDimension(img.getDimension());
}

//------------------destructeur------------------

  Image::~Image()
  {
    #ifdef DEBUG
          cout<<"(Image)  Destructeur "<<endl;
    #endif
  }


//------------------getter------------------

const string  Image::getNom() const
{
    return nom;
}

int  Image::getId() const
{
    return id;
}

const Dimension&  Image::getDimension() const
{
    return dimension;
}

//------------------setter------------------

void  Image::setId(int i)
{
    id=i;
}

void  Image::setNom(const string n)
{
    nom=n;
}

void Image::setDimension(const Dimension& d) 
{ 
    dimension = d; 
    
}

//------------------methodes------------------

void Image::Save(ofstream & fichier) const
{
    fichier.write((char*)&id,sizeof(int));
    int taille = nom.size();
    fichier.write((char*)&taille,sizeof(int));
    fichier.write((char*)nom.data(),taille*sizeof(char));
    dimension.Save(fichier);

}

void Image::Load(ifstream & fichier)
{
    fichier.read((char*)&id,sizeof(int));
    int t;
    fichier.read((char*)&t,sizeof(int));
    nom.resize(t);
    fichier.read((char*)nom.data(),t*sizeof(char));
    dimension.Load(fichier);
}

