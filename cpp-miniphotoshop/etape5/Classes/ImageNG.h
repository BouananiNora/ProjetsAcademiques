#ifndef IMAGENG_H
#define IMAGENG_H

using namespace std;
#include<iostream>
#include "Dimension.h"
#include <string>
#include "Image.h"

class ImageNG : public Image
{
  private:

    int ** matrice;

    //------methodes------

    void initMatrice();

    void rediMatrice(const Dimension&);

    int compImg(const ImageNG&);

  public:
    
    //------constructeur------
    ImageNG();                //par defaut

    ImageNG(int , const string );  //initialisation

    ImageNG(int , const string , const Dimension& );    //nv initialisaiton

    ImageNG(const ImageNG& );      //copie

    ImageNG(const string &);    //initialisation fichier

    //------destructeur------
    ~ImageNG();

    //------methodes------

    void Affiche() const;

    void Dessine ();

    void importFromFile(const string & );

    void exportToFile(const string & ,const string & );

    //------getter------

    int getPixel(const int ,const int ) const;

    int getLuminance() const;

    int getMinimum()const;
    
    int getMaximum()const;

    float getContraste() const;
    
    //------setter------

    void setDimension(const Dimension& ) ;

    void setBackground(const int );

    void setPixel(const int ,const int ,const int );

    //------surcharge------
    ImageNG& operator=(const ImageNG&);

    friend ostream& operator<<(ostream& ,const ImageNG& );

    ImageNG operator+(int );

    ImageNG operator-(int );

    friend ImageNG operator+(int , ImageNG &);

    ImageNG operator++();

    ImageNG operator++(int );

    ImageNG operator--();

    ImageNG operator--(int );

    ImageNG operator-(const ImageNG& );

    int operator<(const ImageNG&  ) ;

    int operator>(const ImageNG&  ) ;

    int operator==(const ImageNG&) ; 

};

#endif