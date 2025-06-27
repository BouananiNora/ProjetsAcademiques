#include "PhotoShop.h"
#include "Dimension.h"
#include "ArrayList.h"
#include "Image.h"

//---------MEMBRE PRIVE--------

int PhotoShop::numCourant = 1;

PhotoShop PhotoShop::instance;

//-------CONSTRUCTEUR PRIVE--------

PhotoShop::PhotoShop()
{
     #ifdef DEBUG
          cout<<"( Photoshop)  Constructeur par defaut "<<endl;
      #endif

    
}

//-------DESTRUCTEUR--------

PhotoShop::~PhotoShop() 
{   
    #ifdef DEBUG
          cout<<"(Photoshop)  Destructeur "<<endl;
    #endif

    reset();
}



//-------METHODES-------

void PhotoShop::reset() 
{
    while (!images.estVide()) 
    {
        images.retireElement(0);
    }

    numCourant=1;
}


void PhotoShop::ajouteImage(Image* pImage) 
{
    if (pImage != NULL) 
    {
        pImage->setId(numCourant++); 
        images.insereElement(pImage); 
    }
}


void PhotoShop::afficheImages() const 
{
    for (int i = 0; i < images.getNombreElements(); i++) 
    {
        Image* img = images.getElement(i);

        img->Affiche(); 
    }
}


void PhotoShop::dessineImages() const 
{
    for (int i = 0; i < images.getNombreElements(); i++) 
    {
        Image* img = images.getElement(i);

        img->Dessine(); 
    }
}


void PhotoShop::supprimeImageParIndice(int indice) 
{
    images.retireElement(indice);
}


void PhotoShop::supprimeImageParId(int id) 
{
    for( int i=0; i< images.getNombreElements(); i++)
    {
        Image* img = images.getElement(i);

        if((img->getId()) == id)
        {
            images.retireElement(i);
            break;
        }
    }

}



//-------GETTER-------

Image* PhotoShop::getImageParIndice(int indice)
{
    
    return images.getElement(indice);
    
}

Image* PhotoShop::getImageParId(int id) 
{
    for( int i=0; i< images.getNombreElements(); i++)
    {
        Image* img = images.getElement(i);

        if((img->getId()) == id)
        {
            return img;
        }
    }
return 0;
}

PhotoShop& PhotoShop::getInstance() 
{
    return instance;
}