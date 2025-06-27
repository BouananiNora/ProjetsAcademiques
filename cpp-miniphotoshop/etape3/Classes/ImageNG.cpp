#include "ImageNG.h"
#include <string.h>
#include "Dimension.h"
#include "MyQT.h"
#include "string.h"
using namespace std;

//------------------methodes--(private)-----------

 void ImageNG::initMatrice()
  {
    matrice=new int* [dimension.getLargeur()];

    for(int x=0;x<dimension.getLargeur(); x++)
    {
      matrice[x] = new int [dimension.getHauteur()];
    }

    setBackground(0);
  }

void ImageNG::rediMatrice(const Dimension& newDimension)
{
    int** newMatrice = new int*[newDimension.getLargeur()];

    for (int x=0; x<newDimension.getLargeur();x++)
    {
        newMatrice[x]=new int[newDimension.getHauteur()];
    }
    
    for (int x=0; x<newDimension.getLargeur();x++)
    {
      for (int y=0; y<newDimension.getHauteur();y++)
      {
        newMatrice[x][y]=0;
      }
    }

    for (int x=0; x<min(newDimension.getLargeur(), dimension.getLargeur());x++)
    {
        for (int y=0; y<min(newDimension.getHauteur(), dimension.getHauteur());y++)
        {
            newMatrice[x][y]=matrice[x][y];
        }
    }
    

    for (int x=0; x<dimension.getLargeur();x++)
    {
        delete[] matrice[x];
    }
    delete[] matrice;

    matrice = newMatrice;
    dimension = newDimension; 

    
}

//------------------constructeur------------------

    ImageNG::ImageNG()                    //par defaut
    {
      #ifdef DEBUG
          cout<<"(ImageNG)  Constructeur par defaut "<<endl;
      #endif

      nom = "Inconnu";
      id=1;
      matrice = NULL;
      initMatrice();
    }

  ImageNG::ImageNG(int i, const string n)   //initialisation
  {
    #ifdef DEBUG
          cout<<"(ImageNG)  Constructeur d'initialisation "<<endl;
    #endif

    setNom(n);
    setId(i);
    matrice=NULL;
    initMatrice();
  }

  ImageNG::ImageNG(int i, const string n, const Dimension& dim)   //initialisation avec dimension
  {
    #ifdef DEBUG
          cout<<"(ImageNG)  Constructeur d'initialisation avec dimension"<<endl;
    #endif

      matrice=NULL;
      setNom(n);
      setId(i);
      setDimension(dim); 
      initMatrice();
  }

  ImageNG::ImageNG(const ImageNG& img)        //copie
  {
    #ifdef DEBUG
        cout<<"(ImageNG)  Constructeur par de copie"<<endl;
    #endif
    
    matrice=NULL;
    setNom(img.getNom());
    setId(img.getId());
    setDimension(img.getDimension());
    initMatrice();
  }

//------------------destructeur------------------

  ImageNG::~ImageNG()
  {
    #ifdef DEBUG
          cout<<"(ImageNG)  Destructeur "<<endl;
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

  void ImageNG::Affiche() const       //maj avvec dimension
  {
    cout << "Nom: " << nom << endl;
    cout << "Id: " << id << endl;
    dimension.Affiche();
  }

  void ImageNG::Dessine()
  {
    MyQT::ViewImage(*this);
  }

  void ImageNG::importFromFile(const string & fichier)
  {
    MyQT::ImportFromFile(*this,fichier.c_str());
  }

  void ImageNG::exportToFile(const string & fichier,const string & format)
  {
    MyQT::ExportToFile(*this,fichier.c_str(),format.c_str());
  }

//------------------getter------------------

  const string ImageNG::getNom() const
  {
    return nom;
  }

  int ImageNG::getId() const
  {
    return id;
  }

  const Dimension& ImageNG::getDimension() const
  {
      return dimension;
  }

  int ImageNG::getPixel(const int x, const int y) const
  {
    return matrice[x][y];
  }
//------------------setter------------------

  void ImageNG::setId(int i)
  {
    id=i;
  }

  void ImageNG::setNom(const string n)
  {
    nom=n;
  }

  void ImageNG::setDimension(const Dimension& dim)
  {
    if (matrice != NULL)
    {
        rediMatrice(dim);
    }
    else
    {
        dimension = dim;
        initMatrice();
    }
  }
  
  void ImageNG::setBackground(const int val)
  {
    for(int x=0; x<dimension.getLargeur();x++)
    {
      for(int y=0; y<dimension.getHauteur();y++)
      {
        setPixel(x,y,val);
      }
    }
  }

  void ImageNG::setPixel(const int x, const int y ,const int val)
  {
    // +Verification

    matrice[x][y]=val;
  }
    





