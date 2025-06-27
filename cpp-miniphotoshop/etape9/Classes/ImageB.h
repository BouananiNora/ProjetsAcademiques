#ifndef IMAGEB_H
#define IMAGEB_H

using namespace std;
#include<iostream>
#include "Dimension.h"
#include <string>
#include "Image.h"
#include "Couleur.h"

class ImageB : public Image
{
    private:

        bool ** matrice;

    //------methodes------

    void initMatrice();

    public:

    //------constructeur------

    ImageB();                //par defaut

    ImageB(int , const string );  //initialisation

    ImageB(int , const string , const Dimension& );    //nv initialisaiton

    ImageB(const ImageB& );      //copie

    

    //------destructeur------

    ~ImageB();   

    //------objet------

    static  Couleur couleurTrue;

    static   Couleur couleurFalse;

    //------methodes------

    void Affiche() const;

    void Dessine ();

    void exportToFile(const string & ,const string & );

    void Save(ofstream & ) const override;

    void Load(ifstream & ) override;

    //------setter------

    void setBackground(bool );

    void setPixel(int ,int ,bool );

    //------getter------
    
    bool getPixel(int ,int ) const;

    //------surcharge------

    ImageB& operator=(const ImageB&);

    friend ostream& operator<<(ostream& ,const ImageB& );

};
#endif
