#ifndef RGBException_H
#define RGBException_H

using namespace std;
#include<iostream>
#include <string>
#include"Exception.h"


class RGBException  : public Exception
{
    private:

        int valeur;

    public:

        //-------CONSTRUCTEUR--------

        RGBException();                    //par defaut

        RGBException(int ,const string & );     //initialisation

        RGBException(const RGBException & );  //copie


        //-------DESTRUCTEUR--------

        ~RGBException();
        

        //-------GETTER-------

        int getVal() const;


        //-------SETTER-------

        void  setVal(int );


        //-------METHODES-------

        void Affiche() const;


};

#endif