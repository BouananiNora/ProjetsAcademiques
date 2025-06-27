#include "ImageB.h"
#include <string.h>
#include "Dimension.h"
#include "Couleur.h"
#include "MyQT.h"
#include "string.h"
#include "Image.h"
#include"XYException.h"
using namespace std;
#include <iostream>
#include <fstream>


//------------------methodes--(private)-----------

 void ImageB::initMatrice()
  {
    
    matrice =new bool* [dimension.getLargeur()];

    for(int x=0;x<dimension.getLargeur(); x++)
    {
      matrice[x] = new bool [dimension.getHauteur()];
    }

    setBackground(false);
  }



//------------------constructeur------------------

    ImageB::ImageB()    :Image()                 //par defaut
    {
      #ifdef DEBUG
          cout<<"(ImageB)  Constructeur par defaut "<<endl;
      #endif

      
      matrice = NULL;
      initMatrice();
    }

  ImageB::ImageB(int i, const string n) : Image(i,n)   //initialisation
  {
    #ifdef DEBUG
          cout<<"(ImageB)  Constructeur d'initialisation "<<endl;
    #endif

    
    matrice=NULL;
    initMatrice();
  }

  ImageB::ImageB(int i, const string n, const Dimension& dim)  : Image(i,n,dim)  //initialisation avec dimension
  {
    #ifdef DEBUG
          cout<<"(ImageB)  Constructeur d'initialisation avec dimension"<<endl;
    #endif

      matrice=NULL;
      
      setDimension(dim); 
      initMatrice();
  }

  ImageB::ImageB(const ImageB& img)    : Image(img)      //copie
  {
    #ifdef DEBUG
        cout<<"(ImageB)  Constructeur par de copie"<<endl;
    #endif
    
    matrice=NULL;
    
    setDimension(img.getDimension());
    initMatrice();
  }

  

//------------------destructeur------------------

  ImageB::~ImageB()
  {
    #ifdef DEBUG
          cout<<"(ImageB)  Destructeur "<<endl;
    #endif

    if(matrice)
    {
      for(int x=0; x<dimension.getLargeur();x++)
      {
        delete[] matrice[x];
      }
      delete[] matrice;
    }
  }



//------------------methodes------------------

  void ImageB::Affiche()  const   //maj avvec dimension
  {
    cout << "Nom: " << nom << endl;
    cout << "Id: " << id << endl;
    dimension.Affiche();
  }

  void ImageB::Dessine()
  {
    MyQT::ViewImage(*this);
  }

  void ImageB::exportToFile(const string & fichier,const string & format)
  {
    MyQT::ExportToFile(*this,fichier.c_str(),format.c_str());
  }

  void ImageB::Save(ofstream& fichier) const 
  {
      Image::Save(fichier);

      for (int x = 0; x < dimension.getLargeur(); x++) 
      {
          for (int y = 0; y < dimension.getHauteur(); y++) 
          {
              int pixel = getPixel(x, y);
              fichier.write((char*)&pixel, sizeof(int));
          }
      }
  }


  void ImageB::Load(ifstream& fichier) 
  {
      Image::Load(fichier);

      for (int x = 0; x < dimension.getLargeur(); x++) 
      {
          for (int y = 0; y < dimension.getHauteur(); y++) 
          {
              int pixel;
              fichier.read((char*)&pixel, sizeof(int));
              setPixel(x, y, pixel);
          }
      }

  }


//------------------objet------------------

 Couleur ImageB::couleurTrue(Couleur(255,255,255));

 Couleur ImageB::couleurFalse(Couleur(0,0,0));



//------------------setter------------------

void ImageB::setBackground(bool val)
{
    for(int x=0; x<dimension.getLargeur();x++)
    {
      for(int y=0; y<dimension.getHauteur();y++)
      {
        setPixel(x,y,val);
      }
    }
  }

  void ImageB::setPixel(int x, int y ,bool val)
  {
    if ( (x >= dimension.getLargeur() ) || (x<0) && (y >= dimension.getHauteur()) || (y<0)) {
        throw XYException('d',"Dimension invalide" );
    }

    if ( (x >= dimension.getLargeur() ) || (x<0))
    {
      throw XYException('x',"largeur invalide" );
    }

    if( (y >= dimension.getHauteur()) || (y<0))
    {
      throw XYException('y',"hauteur invalide" );
    }

    matrice[x][y]=val;
  }



//------------------getter------------------

bool ImageB::getPixel( int x,  int y) const
  {
    if ( (x >= dimension.getLargeur() ) || (x<0) && (y >= dimension.getHauteur()) || (y<0)) {
        throw XYException('d',"Dimension invalide" );
    }

    if ( (x >= dimension.getLargeur() ) || (x<0))
    {
      throw XYException('x',"largeur invalide" );
    }

    if( (y >= dimension.getHauteur()) || (y<0))
    {
      throw XYException('y',"hauteur invalide" );
    }
    return matrice[x][y];
  }



//------------------surcharge------------------


ImageB& ImageB::operator=(const ImageB& img)
  {
    setId(img.getId());
    setNom(img.getNom());
    setDimension(img.getDimension());
    
    if(matrice)
        {
          for(int x=0;x<dimension.getLargeur();x++)
          {
            delete[] matrice[x];
          }
          delete[] matrice;
        }

    initMatrice();

    for(int i=0; i < dimension.getLargeur(); i++)
    {
        for(int j=0; j < dimension.getHauteur(); j++)
        {
            setPixel(i, j, img.getPixel(i, j));
        }
    }

    return (*this);
    
  }

  ostream& operator<<(ostream& s,const ImageB& i)
  {
      s <<"id:"<< i.id << "/nom:" << i.nom << "/dimension:" << i.dimension;
      return s;
  }