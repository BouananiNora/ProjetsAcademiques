#ifndef TRAITEMENTS_H
#define TRAITEMENTS_H


#include "Dimension.h"
#include "ImageB.h"
#include "ImageNG.h"
#include "ImageRGB.h"
#include "Image.h"

using namespace std;
#include <string>

class Traitements
{

    public:

    //--------methodes static-------------
    
    static ImageB Seuillage(const ImageNG& imageIn, int seuil);

    static ImageNG FiltreMoyenneur(const ImageNG& imageIn, int taille) ;

    static ImageNG FiltreMedian(const ImageNG& imageIn, int taille) ;

    static ImageNG Erosion(const ImageNG& imageIn, int taille) ;

    static ImageNG Dilatation(const ImageNG& imageIn, int taille) ;

    static ImageNG Negatif(const ImageNG& imageIn);



};

#endif