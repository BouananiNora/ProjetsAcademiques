

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "Dimension.h"

using namespace std;

class Image
{
    protected:

        int id;
        string nom;
        Dimension dimension;
    
    public:

        //------constructeur------

        Image();                //par defaut

        Image(int , const string & );  //initialisation

        Image(int , const string &, const Dimension& );    //nv initialisaiton

        Image(const Image& );      //copie

        //------destructeur------

        virtual ~Image() ;

        //------getter------

        const string  getNom() const;
    
        int  getId() const;

        const Dimension&  getDimension() const;

        //------setter------

        void  setId(int i);
    
        void  setNom(const string n);
        
        void setDimension(const Dimension& d) ;

        //------methode------
        
        virtual void Affiche() const =0;

        virtual void Dessine()=0;

        virtual void exportToFile(const string & ,const string & )=0;

        

};

#endif 