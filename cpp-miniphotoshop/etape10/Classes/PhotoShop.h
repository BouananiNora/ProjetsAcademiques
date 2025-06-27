
#ifndef PHOTOSHOP_H
#define PHOTOSHOP_H
#include "Image.h"
#include "ArrayList.h"

class PhotoShop
{
    private:

        ArrayList<Image*> images;

        static int numCourant;

        static PhotoShop instance;

    //------constructeur------

        PhotoShop();        //par defaut

        PhotoShop(const PhotoShop&) ;   //de copie

    //------surcharge------

        PhotoShop& operator=(const PhotoShop&) ;

    
    
    public:

    

     //------destructeur------

        ~PhotoShop();
    

    //------methodes------

        void reset();

        void ajouteImage(Image* pImage);

        void afficheImages() const;

        void dessineImages() const;

        void supprimeImageParIndice(int ind);

        void supprimeImageParId(int id);


    //------getter------

        Image* getImageParIndice(int indice);

        Image* getImageParId(int id);

        static PhotoShop& getInstance();

};

#endif
