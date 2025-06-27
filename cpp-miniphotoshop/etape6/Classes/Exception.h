#ifndef EXCEPTION_H
#define EXCEPTION_H

using namespace std;
#include<iostream>
#include <string>

class Exception
{
    protected:

        string message;

    public:

        //-------CONSTRUCTEUR--------

        Exception();                    //par defaut

        Exception(const string & );     //initialisation

        Exception(const Exception & );  //copie


        //-------DESTRUCTEUR--------

        ~Exception();
        

        //-------GETTER-------

        const string getMsg() const;


        //-------SETTER-------

        void  setMsg(const string );


        //-------METHODES-------

        void Affiche() const;

};

#endif