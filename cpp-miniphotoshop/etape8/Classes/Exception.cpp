#include "Exception.h"
#include "MyQT.h"
#include "string.h"
using namespace std;


//-------CONSTRUCTEUR--------

Exception::Exception()                    //par defaut
{
    #ifdef DEBUG
          cout<<"( Exception)  Constructeur par defaut "<<endl;
      #endif

    message="erreur inconnue";

}


Exception::Exception(const string & msg)     //initialisation
{
    #ifdef DEBUG
          cout<<"( Exception)  Constructeur d'initialisation "<<endl;
    #endif

    message=msg;
}


Exception::Exception(const Exception & msg)  //copie
{
    #ifdef DEBUG
        cout<<"( Exception)  Constructeur par de copie"<<endl;
    #endif

    setMsg(msg.getMsg());
}



//-------DESTRUCTEUR--------

Exception::~Exception()
{
    #ifdef DEBUG
          cout<<"( Exception)  Destructeur "<<endl;
    #endif
}



//-------GETTER-------

const string Exception::getMsg() const
{
    return message;
}


//-------SETTER-------

void  Exception::setMsg(const string msg)
{
    message=msg;
}


//-------METHODES-------

void Exception::Affiche() const
{
    cout<<"Message: " << message << endl;
}