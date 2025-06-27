#include "Iterateur.h"

//-------CONSTRUCTEUR--------

template <class T> Iterateur<T>::Iterateur(const ArrayList<T>&l) : p(l),pData(l.pTete)
{
    #ifdef DEBUG
          cout<<"(Iterateur)  Constructeur par defaut "<<endl;
    #endif
}

//-------METHODES-------

template <class T> void Iterateur<T>::reset()
{
    pData=p.pTete;
}

template <class T> bool Iterateur<T>::end()
{
    if(pData == NULL)
    {
		return true;
    }

    return false;
}



//-------SURCHARGES-------

template <class T> bool Iterateur<T>::operator++(int)
{ 
    if (!end()) 
    { 
        pData=pData->suivant; 
        
        return true; 
    } 
    else 
    {
        return false; 
    }

}


template <class T> Iterateur<T>::operator T() const
{
    return pData->valeur;
}


template <class T> T& Iterateur<T>::operator&()
{
    return pData->valeur;
}




// Instanciation Templates

template class Iterateur<int>;
#include "Couleur.h"
template class Iterateur<Couleur>;