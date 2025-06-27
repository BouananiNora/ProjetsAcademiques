#ifndef DIMENSION_H
#define DIMENSION_H

using namespace std;
#include<iostream>

class Dimension 
{
	private:

	    int largeur;
	    int hauteur;

	public:

        //------constructeur------
        
	    Dimension();                    //par defaut

	    Dimension(int , int );        //initialisation

	    Dimension(const Dimension& );	//de copie

	    //------destructeur------

	    ~Dimension();

        //------objets------

	    static const Dimension VGA;

	    static const Dimension HD;
	    
	    static const Dimension FULL_HD;

        //------methodes------

        void Affiche() const;

        //------getter------

	    int getLargeur() const;

	    int getHauteur() const;

        //------setter------

	    void setLargeur(int );

	    void setHauteur(int );

};

#endif
