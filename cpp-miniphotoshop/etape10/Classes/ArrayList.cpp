#include "ArrayList.h"
#include "Exception.h"




//-------CONSTRUCTEUR--------

template <class T> ArrayList<T>::ArrayList()
{ 
    #ifdef DEBUG
          cout<<"(ArrayList)  Constructeur par defaut "<<endl;
    #endif

    pTete=NULL;
}

template <class T> ArrayList<T>::ArrayList(const ArrayList<T>& old)
{ 
    #ifdef DEBUG
        cout<<"(ArrayList)  Constructeur par de copie"<<endl;
    #endif

    
    if (old.pTete == NULL) 
    {
        pTete = NULL;
    } 
    else 
    {
        pTete = new Cellule<T>;
        pTete->valeur = old.pTete->valeur;
        pTete->suivant = NULL;

        Cellule<T>* tmpOld = old.pTete->suivant;
        Cellule<T>* tmpNew = pTete;

        while (tmpOld != NULL) 
        {
            tmpNew->suivant = new Cellule<T>;
            tmpNew = tmpNew->suivant;
            tmpNew->valeur = tmpOld->valeur;
            tmpNew->suivant = NULL;
            tmpOld = tmpOld->suivant;
        }
    }
}



//-------DESTRUCTEUR--------

template <class T> ArrayList<T>::~ArrayList()
{
    #ifdef DEBUG
          cout<<"(ArrayList)  Destructeur "<<endl;
    #endif

    

    while (pTete != NULL)
    {
         Cellule<T> *tmp = pTete;
        pTete = pTete->suivant;
        delete tmp;
    }
}



//-------METHODES-------


template <class T> bool ArrayList<T>::estVide() const
{
    if(pTete == NULL)
		return true;
	else
		return false;
}



template <class T> void ArrayList<T>::Affiche() const
{
    if (estVide()) 
    {
        cout << endl << "Liste:" << endl << "/ (vide)" << endl;
    } 
    else 
    {
        cout << endl << "Liste:" << endl;
        for (Cellule<T>* tmp = pTete; tmp != NULL; tmp = tmp->suivant) 
        {
            cout << "  " << tmp->valeur;
        }
        cout << endl;
    }
}

template <class T> void ArrayList<T>::insereElement(const T & val)
{
    Cellule<T>* tmpVal;
	if(estVide()==true)
    {
		tmpVal = new Cellule<T>;
		tmpVal->valeur = val;
        tmpVal->suivant = NULL;
		pTete = tmpVal;

	} 
    else 
    {
		Cellule<T>* tmp = pTete;

		while(tmp->suivant != NULL) 
        {
			tmp = tmp->suivant;
		}
		
		tmpVal = new Cellule<T>;
		tmpVal->valeur = val;
		tmpVal->suivant = NULL;
		
		tmp->suivant = tmpVal;
	}

}

template <class T> T ArrayList<T>::retireElement(int ind)
{
    Cellule<T>* tmp = pTete;
    Cellule<T>* tmpAvt=NULL;
    T val;

    if(estVide()==true)
    {   
        throw Exception("liste vide");
    }

    if(ind<0 || ind > (getNombreElements()-1)) 
    {
        throw Exception("Indice invalide !");
    }

    if (ind == 0) 
    {
        pTete = pTete->suivant;  
    }
    else
    {
        for (int i = 0; i < ind ; i++) 
        {
            tmpAvt=tmp;
            tmp = tmp->suivant;
        }

        tmpAvt->suivant=tmp->suivant;
    }

    val=tmp->valeur;
    delete tmp;
    
    return val;
    
}



//-------GETTER-------

template <class T>int ArrayList<T>::getNombreElements() const
{
	int i = 0;

	if(estVide()==true)
    {   
        throw Exception("liste vide");
    }
	else 
    {
		Cellule<T>* tmp =pTete;
		
		while(tmp != NULL) 
        {
			tmp = tmp->suivant;
            i++;
		}
	}

    return i;
}
    
template <class T> T& ArrayList<T>::getElement(int ind ) const
{
    if(estVide()==true)
    {   
        throw Exception("liste vide");
    }

    if(ind<0 || ind > (getNombreElements()-1)) 
    {
        throw Exception("Indice invalide !");
    }

    Cellule<T>* tmp = pTete;

    for (int i = 0; i < ind ; i++) 
    {
        tmp = tmp->suivant;
    }

    return tmp->valeur;

    
}



//-------SURCHARGES-------

template <class T> ArrayList<T> & ArrayList<T>::operator=(const ArrayList<T>& liste )
{
	Cellule<T> *tmp= liste.pTete;

    while(tmp!=NULL)
    {
        insereElement(tmp->valeur);
        tmp=tmp->suivant;
    }

    return *this;
}






// Instanciation Templates



template class ArrayList<int>;
#include "Couleur.h"

template class ArrayList<Couleur>;

#include "Image.h"
template class ArrayList<Image*>;
