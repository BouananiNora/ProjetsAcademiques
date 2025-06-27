#include "PhotoShop.h"
#include "Dimension.h"
#include "ArrayList.h"
#include "Image.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "ImageNG.h"
#include "ImageRGB.h"
#include "ImageB.h"
#include "Couleur.h"
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
   ImageB::couleurTrue = Couleur::BLANC;  // CORRECT
ImageB::couleurFalse = Couleur::NOIR;  // CORRECT


    while (!images.estVide()) 
    {
        Image* image = images.retireElement(0);
        delete image;
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

int PhotoShop::importeImages(string nomFichier)
{
    ifstream fichier(nomFichier);

    if (!fichier.is_open()) 
    {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << nomFichier << endl;
        return 0;
    }

    int nombreImagesImportees = 0;
    string ligne;

    while (getline(fichier, ligne)) 
    {
        stringstream ss(ligne);
        string typeImage, cheminFichier, nomImage;

        getline(ss, typeImage, ';');
        getline(ss, cheminFichier, ';');
        getline(ss, nomImage, ';');

        Image* image = NULL;

        if (typeImage == "NG") 
        {
            image = new ImageNG(cheminFichier); 
        } else if (typeImage == "RGB") 
        {
            image = new ImageRGB(cheminFichier); 
        } else 
        {
            cerr << "Type d'image inconnu: " << typeImage << endl;
            continue;
        }

        if (image) {
            image->setNom(nomImage); 
            
            PhotoShop::getInstance().ajouteImage(image);
            nombreImagesImportees++;
        }
    }

    fichier.close();
    return nombreImagesImportees;
}


void PhotoShop::Save(const string& filename) const 
{
    ofstream file(filename, ios::binary);

    if (!file.is_open()) 
    {
        cerr << "Erreur: Impossible d'ouvrir le fichier pour l'écriture." << endl;
        return;
    }

    file.write((char*)&numCourant, sizeof(numCourant));

    file.write((char*)&ImageB::couleurTrue, sizeof(Couleur));
    file.write((char*)&ImageB::couleurFalse, sizeof(Couleur));

    int nombreImages = images.getNombreElements();
    file.write((char*)&nombreImages, sizeof(int));

    for (int i = 0; i < nombreImages; ++i) 
    {
        Image* image = images.getElement(i);

        int type;
        if (dynamic_cast<ImageNG*>(image)) 
        {
            type = 1;
        } 
        else if (dynamic_cast<ImageRGB*>(image)) 
        {
            type = 2;
        } 
        else if (dynamic_cast<ImageB*>(image)) 
        {
            type = 3;
        }

        file.write((char*)&type, sizeof(type));
        image->Save(file); 
    }

    file.close();
}

void PhotoShop::Load(const string& filename) 
{


    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier pour la lecture." << endl;
        return;
    }

    file.read((char*)&numCourant, sizeof(numCourant));

    file.read((char*)&ImageB::couleurTrue, sizeof(Couleur));
    file.read((char*)&ImageB::couleurFalse, sizeof(Couleur));

    int nombreImages;
    file.read((char*)&nombreImages, sizeof(int));

    reset(); 

    for (int i = 0; i < nombreImages; ++i) 
    {
        int type;
        file.read((char*)&type, sizeof(type));

        Image* image = NULL;
        switch (type) 
        {
            case 1:
                image = new ImageNG();
                break;
            case 2:
                image = new ImageRGB();
                break;
            case 3:
                image = new ImageB();
                break;
            default:
                cerr << "Type d'image inconnu lors du chargement: " << type << endl;
                continue;
        }

        if (image) 
        {
            image->Load(file); 
            images.insereElement(image); 
        }
    }

    file.close();
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



Image* PhotoShop::operande1 = NULL;
Image* PhotoShop::operande2 = NULL;
Image* PhotoShop::resultat  = NULL;