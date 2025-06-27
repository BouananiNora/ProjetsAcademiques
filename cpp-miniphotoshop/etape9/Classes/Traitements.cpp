#include "Traitements.h"
#include "Exception.h"
#include <iostream>


//--------Seuillage-------------
ImageB Traitements::Seuillage(const ImageNG& imageIn, int seuil)
{
    Dimension dim = imageIn.getDimension();
    ImageB imageOut(imageIn.getId(), imageIn.getNom() , dim);

    for (int x = 0; x < dim.getLargeur(); ++x)
    {
        for (int y = 0; y < dim.getHauteur(); ++y)
        {
            int niveauGris = imageIn.getPixel(x, y);
            
            if (niveauGris >= seuil) 
            {
                imageOut.setPixel(x, y, true); 
            } 
            else 
            {
                imageOut.setPixel(x, y, false); 
            }
        }
    }

    
    imageOut.setNom(imageIn.getNom() + "-seuil" + to_string(seuil));

    return imageOut;
}


//--------FiltreMoyenneur-------------

ImageNG Traitements::FiltreMoyenneur(const ImageNG& imageIn, int taille) 
{
    if (taille % 2 == 0) 
    {
        throw Exception("la taille du filtre doit etre un nombre impair ");
    }

    Dimension dim = imageIn.getDimension();
    ImageNG imageOut(imageIn.getId(), imageIn.getNom() , dim);

    int caree = taille / 2;

    for (int x = 0; x < dim.getLargeur(); x++) 
    {
        for (int y = 0; y < dim.getHauteur(); y++) 
        {
            int somme = 0;
            int count = 0;

            for (int i = -caree; i < caree; i++) 
            {
                for (int j = -caree; j < caree; j++) 
                {
                    int nx = x + i;
                    int ny = y + j;

                    if (nx >= 0 && nx < dim.getLargeur() && ny >= 0 && ny < dim.getHauteur()) 
                    {
                        somme += imageIn.getPixel(nx, ny);
                        count++;
                    }
                }
            }

            int moyenne = somme / count;

            imageOut.setPixel(x, y, moyenne);
        }
    }

    imageOut.setNom(imageIn.getNom() + "-moyenne" + to_string(taille));

    return imageOut;
}


//--------FiltreMedian-------------

ImageNG Traitements::FiltreMedian(const ImageNG& imageIn, int taille) 
{
    if (taille % 2 == 0) 
    {
        throw Exception("La taille du filtre doit être un nombre impair.");
    }

    Dimension dim = imageIn.getDimension();
    ImageNG imageOut(imageIn.getId(), imageIn.getNom(), dim);

    int caree = taille / 2;
    int* pixels = new int[taille * taille]; 

    for (int x = 0; x < dim.getLargeur(); x++) 
    {

        for (int y = 0; y < dim.getHauteur(); y++) 
        {

            int count = 0;

            for (int i = -caree; i <= caree; i++) 
            {

                for (int j = -caree; j <= caree; j++) 
                {
                    int nx = x + i;
                    int ny = y + j;

                    if (nx >= 0 && nx < dim.getLargeur() && ny >= 0 && ny < dim.getHauteur()) 
                    {
                        pixels[count++] = imageIn.getPixel(nx, ny);
                    } 
                    else 
                    {
                        pixels[count++] = 0; 
                    }
                }
            }


            for (int i = 0; i < count - 1; i++) 
            {

                for (int j = i + 1; j < count; j++)
                {

                    if (pixels[i] > pixels[j])  //trier tab en croiss 
                    {
                        int tmp = pixels[i];
                        pixels[i] = pixels[j];
                        pixels[j] = tmp;
                    }
                }
            }
            

            int mediane = pixels[taille / 2];
            imageOut.setPixel(x, y, mediane);
        }
    }

    imageOut.setNom(imageIn.getNom() + "-median" + to_string(taille));

    return imageOut;
}


//--------Erosion-------------

ImageNG Traitements::Erosion(const ImageNG& imageIn, int taille) 
{
    if (taille % 2 == 0) 
    {
        throw Exception("La taille du filtre doit être un nombre impair.");
    }

    Dimension dim = imageIn.getDimension();
    ImageNG imageOut(imageIn.getId(), imageIn.getNom(), dim);

    int caree = taille / 2;
    int* pixels = new int[taille * taille]; 

    for (int x = 0; x < dim.getLargeur(); x++) 
    {

        for (int y = 0; y < dim.getHauteur(); y++) 
        {

            int count = 0;

            for (int i = -caree; i <= caree; i++) 
            {
                for (int j = -caree; j <= caree; j++) 
                {
                    int nx = x + i;
                    int ny = y + j;

                    if (nx >= 0 && nx < dim.getLargeur() && ny >= 0 && ny < dim.getHauteur()) 
                    {
                        pixels[count++] = imageIn.getPixel(nx, ny);
                    } 
                    else 
                    {
                        pixels[count++] = 0; 
                    }
                }
            }

            int min = pixels[0];

            for (int k = 1; k < count; k++) 
            {
                if (pixels[k] < min) 
                {
                    min = pixels[k];
                }
            }

            imageOut.setPixel(x, y, min);
        }
    }

    imageOut.setNom(imageIn.getNom() + "-erode" + to_string(taille));

    return imageOut;
}


//--------Dilatation-------------

ImageNG  Traitements::Dilatation(const ImageNG& imageIn, int taille) 
{
    if (taille % 2 == 0) 
    {
        throw Exception("La taille du filtre doit être un nombre impair.");
    }

    Dimension dim = imageIn.getDimension();
    ImageNG imageOut(imageIn.getId(), imageIn.getNom(), dim);

    int caree = taille / 2;
    int* pixels = new int[taille * taille]; 

    for (int x = 0; x < dim.getLargeur(); x++) 
    {

        for (int y = 0; y < dim.getHauteur(); y++) 
        {

            int count = 0;

            for (int i = -caree; i <= caree; i++) 
            {
                for (int j = -caree; j <= caree; j++) 
                {
                    int nx = x + i;
                    int ny = y + j;

                    if (nx >= 0 && nx < dim.getLargeur() && ny >= 0 && ny < dim.getHauteur()) 
                    {
                        pixels[count++] = imageIn.getPixel(nx, ny);
                    } 
                    else 
                    {
                        pixels[count++] = 0; 
                    }
                }
            }

            int max = pixels[0];

            for (int k = 1; k < count; k++) 
            {
                if (pixels[k] > max) 
                {
                    max = pixels[k];
                }
            }

            imageOut.setPixel(x, y, max);
        }
    }

    imageOut.setNom(imageIn.getNom() + "-erode" + to_string(taille));

    return imageOut;
}


//--------Negatif-------------

ImageNG Traitements::Negatif(const ImageNG& imageIn) 
{
    Dimension dim = imageIn.getDimension();
    ImageNG imageOut(imageIn.getId(), imageIn.getNom(), dim);

    for (int x = 0; x < dim.getLargeur(); x++) 
    {
        for (int y = 0; y < dim.getHauteur(); y++) 
        {
            int valPixel = imageIn.getPixel(x, y);

            int valNegatif = 255 - valPixel;

            imageOut.setPixel(x, y, valNegatif);
        }
    }

    imageOut.setNom(imageIn.getNom() + "-negatif");

    return imageOut;
}