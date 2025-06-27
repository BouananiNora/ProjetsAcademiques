#ifndef IMAGERGB_H
#define IMAGERGB_H

using namespace std;
#include<iostream>
#include "Dimension.h"
#include <string>
#include "Image.h"
#include"Couleur.h"

class ImageRGB : public Image
{
    private:

    Couleur ** matrice;

    //------methodes------

    void initMatrice();

    public:

    //------constructeur------

    ImageRGB();                //par defaut

    ImageRGB(int , const string );  //initialisation

    ImageRGB(int , const string , const Dimension& );    //nv initialisaiton

    ImageRGB(const ImageRGB& );      //copie

    ImageRGB(const string &);    //initialisation fichier

    //------destructeur------

    ~ImageRGB();

    //------methodes------

    void Affiche() const ;

    void Dessine ();

    void importFromFile(const string & );

    void exportToFile(const string & ,const string & );

    //------setter------

    void setBackground(const Couleur& );

    void setPixel(int ,int ,const Couleur& );

    //------getter------
    
    Couleur& getPixel(int ,int ) const;

    //------surcharge------

    ImageRGB& operator=(const ImageRGB&);

    friend ostream& operator<<(ostream& ,const ImageRGB& );

};
#endif