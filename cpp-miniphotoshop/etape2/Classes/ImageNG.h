#ifndef IMAGENG_H
#define IMAGENG_H

using namespace std;
#include<iostream>
#include "Dimension.h"
#include <string>


class ImageNG
{
  private:

    int id;
    string nom;
    Dimension dimension;

  public:
    
    //------constructeur------
    ImageNG();                //par defaut

    ImageNG(int , const string );  //initialisation

    ImageNG(int , const string , const Dimension& );    //nv initialisaiton

    ImageNG(const ImageNG& );      //copie

    //------destructeur------
    ~ImageNG();

    //------methodes------

    void Affiche() const;

    //------getter------

    const string getNom() const;

    int getId() const;

    const Dimension& getDimension() const;

    //------setter------
    void setId(int );

    void setNom(const string );

    void setDimension(const Dimension& );

    
};

#endif