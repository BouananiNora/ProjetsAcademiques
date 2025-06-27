#include "ImageNG.h"
#include <string.h>
#include "Dimension.h"

//------------------constructeur------------------

    ImageNG::ImageNG()                    //par defaut
    {
      #ifdef DEBUG
          cout<<"(ImageNG)  Constructeur par defaut "<<endl;
      #endif

      nom = "Inconnu";
      id=1;
    }

  ImageNG::ImageNG(int i, const string n)   //initialisation
  {
    #ifdef DEBUG
          cout<<"(ImageNG)  Constructeur d'initialisation "<<endl;
    #endif

    setNom(n);
    setId(i);
  }

  ImageNG::ImageNG(int i, const string n, const Dimension& dim)   //initialisation avec dimension
  {
    #ifdef DEBUG
          cout<<"(ImageNG)  Constructeur d'initialisation avec dimension"<<endl;
    #endif
      setNom(n);
      setId(i);
      setDimension(dim);
  }

  ImageNG::ImageNG(const ImageNG& img)        //copie
  {
    #ifdef DEBUG
        cout<<"(ImageNG)  Constructeur par de copie"<<endl;
    #endif

    setNom(img.getNom());
    setId(img.getId());
    setDimension(img.getDimension());
  }

//------------------destructeur------------------

  ImageNG::~ImageNG()
  {
    #ifdef DEBUG
          cout<<"(ImageNG)  Destructeur "<<endl;
    #endif
  }

//------------------methodes------------------

  void ImageNG::Affiche() const       //maj avvec dimension
  {
    cout << "Nom: " << nom << endl;
    cout << "Id: " << id << endl;
    dimension.Affiche();
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
      dimension = dim;
  }

    





