#include "ImageNG.h"
#include <string.h>

//------------------constructeur------------------

    ImageNG::ImageNG()                    //par defaut
    {
      #ifdef DEBUG
          cout<<"(ImageNG)  Constructeur par defaut "<<endl;
      #endif

      nom = NULL;
      setNom("Inconnu");
      id=1;
    }

  ImageNG::ImageNG(int i, const char* n)   //initialisation
  {
    #ifdef DEBUG
          cout<<"(ImageNG)  Constructeur d'initialisation "<<endl;
    #endif

    nom = NULL;
    setNom(n);
    setId(i);
  }

  ImageNG::ImageNG(const ImageNG& img)        //copie
  {
    #ifdef DEBUG
        cout<<"(ImageNG)  Constructeur par de copie"<<endl;
    #endif

    nom=NULL;
    setNom(img.getNom());
    setId(img.getId());
  }

//------------------destructeur------------------

  ImageNG::~ImageNG()
  {
    #ifdef DEBUG
          cout<<"(ImageNG)  Destructeur "<<endl;
    #endif

    if(nom) 
    {
        delete nom;
    }
  }

//------------------methodes------------------

  void ImageNG::Affiche() const
  {
    cout << "Nom: " << nom << endl;
    cout << "Id: " << id << endl;
  }

//------------------getter------------------

  const char* ImageNG::getNom() const
  {
    return nom;
  }

  int ImageNG::getId() const
  {
    return id;
  }

//------------------setter------------------

  void ImageNG::setId(int i)
  {
    id=i;
  }

  void ImageNG::setNom(const char* n)
  {
    if(nom)
    {
        delete nom;
    }

    if(n==NULL)
    {
        nom=NULL;
        return;
    }

    nom=new char[strlen(n)+1];
    strcpy(nom,n);
  }
