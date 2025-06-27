#include "Exception.h"
#include "RGBException.h"
#include <iostream>
#include "string.h"
using namespace std;


//-------CONSTRUCTEUR--------

RGBException::RGBException()  :Exception()                  //par defaut
{
    #ifdef DEBUG
          cout<<"( RGBException)  Constructeur par defaut "<<endl;
      #endif

    setVal(0);
}


RGBException::RGBException(int val,const string & msg)   : Exception(msg)   //initialisation
{
    #ifdef DEBUG
          cout<<"( RGBException)  Constructeur d'initialisation "<<endl;
    #endif

    setVal(val);
}


RGBException::RGBException(const RGBException &msg)  : Exception(msg) //copie
{
    #ifdef DEBUG
        cout<<"( RGBException)  Constructeur par de copie"<<endl;
    #endif

    setVal(msg.getVal());
}



//-------DESTRUCTEUR--------

RGBException::~RGBException()
{
    #ifdef DEBUG
          cout<<"( RGBException)  Destructeur "<<endl;
    #endif
}



//-------GETTER-------

int  RGBException::getVal() const
{
    return valeur;
}



//-------SETTER-------

void  RGBException::setVal(int val)
{
    valeur=val;
}



//-------METHODES-------

void RGBException::Affiche() const
{
    Exception :: Affiche();
    cout<<"Valeur: " << valeur<< endl;
}