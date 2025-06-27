#include "ImageRGB.h"
#include <string.h>
#include "Dimension.h"
#include "Couleur.h"
#include "MyQT.h"
#include "string.h"
#include "Image.h"
using namespace std;

//------------------methodes--(private)-----------

 void ImageRGB::initMatrice()
  {
    matrice=new Couleur* [dimension.getLargeur()];

    for(int x=0;x<dimension.getLargeur(); x++)
    {
      matrice[x] = new Couleur [dimension.getHauteur()];
    }

    setBackground(Couleur(0,0,0));
  }
//------------------constructeur------------------

    ImageRGB::ImageRGB()   :Image()                  //par defaut
    {
      #ifdef DEBUG
          cout<<"(ImageRGB)  Constructeur par defaut "<<endl;
      #endif

      
      matrice = NULL;
      initMatrice();
    }

  ImageRGB::ImageRGB(int i, const string n) : Image(i,n)   //initialisation
  {
    #ifdef DEBUG
          cout<<"(ImageRGB)  Constructeur d'initialisation "<<endl;
    #endif

    
    matrice=NULL;
    initMatrice();
  }

  ImageRGB::ImageRGB(int i, const string n, const Dimension& dim) : Image(i,n,dim)  //initialisation avec dimension
  {
    #ifdef DEBUG
          cout<<"(ImageRGB)  Constructeur d'initialisation avec dimension"<<endl;
    #endif

      matrice=NULL;
      
      setDimension(dim); 
      initMatrice();
  }

  ImageRGB::ImageRGB(const ImageRGB& img)  : Image(img)       //copie
  {
    #ifdef DEBUG
        cout<<"(ImageRGB)  Constructeur par de copie"<<endl;
    #endif
    
    matrice=NULL;
    
    setDimension(img.getDimension());
    initMatrice();
  }

  ImageRGB::ImageRGB(const string &fichier )    : Image()           //initialisation fichier
    {
      #ifdef DEBUG
          cout<<"(ImageRGB)  Constructeur par defaut "<<endl;
      #endif

      
      matrice = NULL;
      initMatrice();
      importFromFile(fichier);

    }
//------------------destructeur------------------

  ImageRGB::~ImageRGB()
  {
    #ifdef DEBUG
          cout<<"(ImageRGB)  Destructeur "<<endl;
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

  void ImageRGB::Affiche() const      //maj avvec dimension
  {
    cout << "Nom: " << nom << endl;
    cout << "Id: " << id << endl;
    dimension.Affiche();
  }

  void ImageRGB::Dessine()
  {
    MyQT::ViewImage(*this);
  }

  void ImageRGB::importFromFile(const string & fichier)
  {
    MyQT::ImportFromFile(*this,fichier.c_str());
  }

  void ImageRGB::exportToFile(const string & fichier,const string & format)
  {
    MyQT::ExportToFile(*this,fichier.c_str(),format.c_str());
  }

//------------------setter------------------

void ImageRGB::setBackground(const Couleur& val)
{
    for(int x=0; x<dimension.getLargeur();x++)
    {
      for(int y=0; y<dimension.getHauteur();y++)
      {
        setPixel(x,y,val);
      }
    }
  }

  void ImageRGB::setPixel(int x, int y ,const Couleur& val)
  {
    // +Verification

    matrice[x][y]=val;
  }

//------------------getter------------------

Couleur& ImageRGB::getPixel( int x,  int y) const
  {
    return matrice[x][y];
  }

//------------------surcharge------------------


ImageRGB& ImageRGB::operator=(const ImageRGB& img)
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

  ostream& operator<<(ostream& s,const ImageRGB& i)
  {
      s << i.id << "/" << i.nom << "/" << i.dimension;
      return s;
  }