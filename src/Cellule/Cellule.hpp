#ifndef CELLULE_H_INCLUDE
#define CELLULE_H_INCLUDE
#include <fstream>
    template <class T>  class Cellule{
    protected:
        T valeur;
        Cellule<T>  * precedent, *suivant;
    public:
        int previous( Cellule<T> *);
        int next( Cellule<T> *);
        int set(T);
        T get();
        Cellule<T>* get_prev();
        Cellule<T>* get_next();
        Cellule();
        Cellule(T);
        ~Cellule();
        Cellule<T>& operator= (const Cellule<T> &);
        friend int operator== (Cellule<T>  c1,Cellule<T>  c2){
            return c1.get() == c2.get();
        };
        friend int operator< (Cellule<T>  c1,Cellule<T>  c2){
            return c1.get() < c2.get();
        };
        friend int operator<= ( Cellule<T>  c1,Cellule<T>  c2){
            return c1.get() <= c2.get();
        };
        friend int operator> (const Cellule<T> & c1,const Cellule<T> & c2){
            return c1.get() > c2.get();
        };
        friend std::ostream& operator<<(std::ostream &os, const Cellule<T> &b){
            
            os << b.valeur;
            return os;
        };
        friend std::istream& operator>>(std::istream &os,Cellule<T> &b){
            if(!os)return os;
            os >> b.valeur;
            return os;
        };

    };
#include "Cellule.hpp"
#include "stdlib.h"
#include <fstream>
    
    
    template <class T> int Cellule<T>::set( T val){
        valeur = val;
        return 1;
    }
    template <class T> int Cellule<T>::next( Cellule<T>* n){
        suivant = n;
        return 1;
    }
    template <class T> int Cellule<T>::previous( Cellule<T>* p){
        precedent = p;
        return 1;
    }
    template <class T> T Cellule<T>::get(){
        return valeur;
    }
    template <class T> Cellule<T> * Cellule<T>::get_next(){
        return suivant;
    }
    template <class T> Cellule<T> * Cellule<T>::get_prev(){
        return precedent;
    }

    template <class T> Cellule<T>::Cellule()
    {
        precedent = suivant = NULL;
    }
 
    template <class T> Cellule<T>::Cellule(T val)
    {
        precedent = suivant = NULL;
        valeur = val;
    };
    template <class T> Cellule<T>::~Cellule()
    {
    };
    template <class T> Cellule<T> & Cellule<T>::operator= (const Cellule<T> & c){
        if(&c != this){
            valeur = c.valeur;
        }
        return * this;
    };

#endif
