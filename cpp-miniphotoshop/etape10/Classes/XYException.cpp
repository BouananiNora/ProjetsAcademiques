#include "Exception.h"
#include "XYException.h"
#include <iostream>
#include "string.h"
using namespace std;


//-------CONSTRUCTEUR--------

XYException::XYException()     :Exception()               //par defaut
{
    #ifdef DEBUG
          cout<<"( XYException)  Constructeur par defaut "<<endl;
      #endif
    
    setCrd('d');
}


XYException::XYException(char crd,const string & msg)  : Exception(msg)      //initialisation
{
    #ifdef DEBUG
          cout<<"( XYException)  Constructeur d'initialisation "<<endl;
    #endif

    setCrd(crd);
}


XYException::XYException(const XYException & msg) :Exception(msg)    //copie
{
    #ifdef DEBUG
        cout<<"( XYException)  Constructeur par de copie"<<endl;
    #endif

    setCrd(msg.getCrd());
}



//-------DESTRUCTEUR--------

XYException::~XYException()
{
    #ifdef DEBUG
          cout<<"( XYException)  Destructeur "<<endl;
    #endif
}
 

//-------GETTER-------

char XYException::getCrd() const 
{
    return coordonee;
}
 

//-------SETTER-------

void  XYException::setCrd(char crd ) 
{
    coordonee=crd;
}
 

//-------SURCHARGES-------

bool XYException::operator<(const XYException& crd) const 
{
    return coordonee < crd.coordonee;
}

bool XYException::operator>(const XYException& crd) const 
{
    return coordonee > crd.coordonee;
}

bool XYException::operator==(const XYException& crd) const 
{
    return coordonee == crd.coordonee;
}
 


 //-------METHODES-------

void XYException::Affiche() const
{
    Exception :: Affiche();
    cout<<"Coordonnee: " << coordonee<< endl;
}