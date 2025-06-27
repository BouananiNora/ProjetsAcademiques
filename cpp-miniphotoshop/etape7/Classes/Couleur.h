#ifndef COULEUR_H
#define COULEUR_H

using namespace std;
#include<iostream>

#include <string>

class Couleur 
{
    private:

        int rouge;
        int vert;
        int bleu;

    public:

    //------constructeur------
        Couleur();                //par defaut

        Couleur(int , int ,int );  //initialisation

        Couleur(const Couleur& );      //copie

    //------destructeur------

	    ~Couleur();

    //------objets------Dimension

        static Couleur ROUGE;
        static Couleur VERT;
        static Couleur BLEU;
        static Couleur BLANC;
        static Couleur NOIR;

    //------getter------

        int getRouge() const;

        int getVert()const ;

        int getBleu() const ;

    //------setter------

        void setRouge(int );

        void setVert(int );

        void setBleu(int );

    //------surcharge------

    friend ostream& operator<<(ostream& ,const Couleur& );

    Couleur & operator=(const Couleur&);

    //------methodes------

    void Affiche() ;

    

};

#endif