#ifndef ITERATEUR_H
#define ITERATEUR_H

using namespace std;
#include <iostream>
#include <string>
#include "ArrayList.h"


template<class T> class Iterateur
{
    private:

        const ArrayList<T> & p;

        Cellule<T> *pData;

    public:

        //------constructeur------

        Iterateur (const ArrayList<T> &) ;       //initialisation


        //------methodes------

        void reset();

        bool end();


        //------surcharge------

        bool operator++(int);

        operator T() const;

        T& operator&();

};

#endif
