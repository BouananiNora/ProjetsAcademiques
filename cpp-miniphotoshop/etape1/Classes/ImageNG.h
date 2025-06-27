#ifndef IMAGENG_H
#define IMAGENG_H

using namespace std;
#include<iostream>

class ImageNG
{
  private:

    int id;
    char* nom;

  public:
    
    //------constructeur------
    ImageNG();                //par defaut

    ImageNG(int , const char* );  //initialisation

    ImageNG(const ImageNG& );      //copie

    //------destructeur------
    ~ImageNG();

    //------methodes------

    void Affiche() const;

    //------getter------

    const char * getNom() const;

    int getId() const;

    //------setter------
    void setId(int );

    void setNom(const char* );

    
};

#endif