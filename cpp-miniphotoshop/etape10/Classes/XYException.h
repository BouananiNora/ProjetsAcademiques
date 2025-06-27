#ifndef XYEXCEPTION_H
#define XYEXCEPTION_H

using namespace std;
#include<iostream>
#include <string>
#include"Exception.h"


class XYException  : public Exception
{
    private:

        char coordonee;

    public:

        //-------CONSTRUCTEUR--------

        XYException();                    //par defaut

        XYException(char ,const string & );     //initialisation

        XYException(const XYException & );  //copie


        //-------DESTRUCTEUR--------

        ~XYException();
        

        //-------GETTER-------

        char getCrd() const;


        //-------SETTER-------

        void  setCrd(char );


        //-------SURCHARGES-------

        bool operator<(const XYException& ) const ;

        bool operator>(const XYException& ) const;

        bool operator==(const XYException& ) const;


        //-------METHODES-------

        void Affiche() const;
};

#endif