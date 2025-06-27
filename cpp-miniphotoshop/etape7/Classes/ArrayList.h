#ifndef ARRAYLIST_H
#define ARRAYLIST_H

using namespace std;
#include <iostream>
#include <string>


template<class T> struct Cellule
{
    T valeur ;

    Cellule<T> *suivant ;
};

template<class T> class Iterateur; 

template<class T> class ArrayList 
{
    private:

        Cellule<T>  *pTete;


    public:
        

    //------constructeur------

    ArrayList();                        //par defaut

    ArrayList(const ArrayList<T>& );    //de copie



    //------destructeur------

    ~ArrayList();



    //------methodes------

    bool estVide() const;

    void Affiche() const;

    void insereElement(const T & );

    T retireElement(int );



    //------getter------

    int getNombreElements() const;
    
    T& getElement(int ) const;
    


    //------surcharge------

    ArrayList<T>& operator=(const ArrayList<T>& );


    //------template amie------

    friend class Iterateur<T>;

    
};


#endif
