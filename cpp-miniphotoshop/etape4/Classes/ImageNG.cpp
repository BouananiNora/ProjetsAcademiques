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

int ImageNG::compImg(const ImageNG&img)
{

    for (int x = 0; x < dimension.getLargeur(); x++) 
    {
        for (int y = 0; y < dimension.getHauteur(); y++) 
        {

            if(matrice[x][y] < img.matrice[x][y]) return -1;
            if(matrice[x][y] > img.matrice[x][y]) return 1;   
        }
    }
    return 0;
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

  ImageNG::ImageNG(const string &fichier )           //initialisation fichier
    {
      #ifdef DEBUG
          cout<<"(ImageNG)  Constructeur par defaut "<<endl;
      #endif

      nom = "Inconnu";
      id=1;
      matrice = NULL;
      initMatrice();
      importFromFile(fichier);

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

  int ImageNG::getLuminance()  const
  {
    int luminance = 0;

    for (int x = 0; x < dimension.getLargeur(); x++) {
        for (int y = 0; y < dimension.getHauteur(); y++) {
            luminance += matrice[x][y];
        }
    }

    luminance=luminance / (dimension.getLargeur() * dimension.getHauteur());

    return luminance ;
  }

  int ImageNG::getMinimum() const
  {
    int minLuminance = matrice[0][0];;

    for (int x = 0; x < dimension.getLargeur(); x++) 
    {
        for (int y = 0; y < dimension.getHauteur(); y++) 
        {
          if(matrice[x][y]<minLuminance)
          {
            minLuminance = matrice[x][y];
          }        
        }
    }

    return minLuminance ;
  }

  int ImageNG::getMaximum() const
  {
    int maxLuminance = matrice[0][0];;

    for (int x = 0; x < dimension.getLargeur(); x++) 
    {
        for (int y = 0; y < dimension.getHauteur(); y++) 
        {
          if(matrice[x][y]>maxLuminance)
          {
            maxLuminance = matrice[x][y];
          }        
        }
    }

    return maxLuminance ;
  }

  float ImageNG::getContraste() const
  {
    float contraste;
    int max=getMaximum();
    int min=getMinimum();

    contraste= float(max-min)/float(max+min) ;
        
    return contraste ;
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
    if(val>=0 && val<=255)
    {
      matrice[x][y]=val;
    }
    else
    {
      //exception
      return;
    }
    
  }
    
//------------------surcharge------------------

  ImageNG& ImageNG::operator=(const ImageNG& img)
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

  ostream& operator<<(ostream& s,const ImageNG& i)
  {
      s << i.id << "/" << i.nom << "/" << i.dimension << "/" << i.getLuminance() << "/" << i.getContraste();
      return s;
  }


  ImageNG ImageNG::operator+(int val)
  {
    ImageNG imgPlus=*this;

    for(int x=0;x<imgPlus.dimension.getLargeur();x++)
    {
      for(int y=0;y<imgPlus.dimension.getHauteur();y++)
      {
          int nvGris=getPixel(x,y)+val;
          
          imgPlus.setPixel(x,y,nvGris);
      }
    }

    return imgPlus;
  }

  ImageNG ImageNG::operator-(int val)
  {
    ImageNG imgMoins(*this);

    for(int x=0;x<imgMoins.dimension.getLargeur();x++)
    {
      for(int y=0;y<imgMoins.dimension.getHauteur();y++)
      {
          int nvGris=getPixel(x,y)-val;
          
          imgMoins.setPixel(x,y,nvGris);
      }
    }

    return imgMoins;
  }

  ImageNG operator+(int val, ImageNG & img)
  {
    return img + val;
  }

  ImageNG ImageNG::operator++() 
  {
    (*this)=(*this)+20;
    return *this;
  }
  
  ImageNG ImageNG::operator++(int val)
  {
    ImageNG  img(*this);
    (*this)=(*this)+20;
    return img;
  }

  ImageNG ImageNG::operator--() 
  {
    (*this)=(*this)-20;
    return *this;
  }

  ImageNG ImageNG::operator--(int val)
  {
    ImageNG  img(*this);
    (*this)=(*this)-20;
    return img;
  }

  ImageNG ImageNG::operator-(const ImageNG& img)
  {
    ImageNG resImg(*this);

    for (int x = 0; x < min(dimension.getLargeur(),img.dimension.getLargeur()); x++) 
    {
        for (int y = 0; y < min(dimension.getHauteur(),img.dimension.getHauteur()); y++) 
        {
            int val=getPixel(x,y)-img.getPixel(x,y);
            resImg.setPixel(x,y,val);
        }
    }
    return resImg;
  }

  int ImageNG::operator<(const ImageNG& img ) 
  {
    return compImg(img)==-1;
  }
    
  int ImageNG::operator>(const ImageNG& img ) 
  {
      return compImg(img)==1;
  }

  int ImageNG::operator==(const ImageNG& img) 
  {
      return compImg(img)==0;
  }