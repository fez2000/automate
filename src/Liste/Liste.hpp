#ifndef LISTE_H_INCLUDE
#define LISTE_H_INCLUDE
#include "../Cellule/Cellule.hpp"
#include <iostream>
#include <fstream>
template <class T>class Liste
{
protected:
    Cellule<T> * tete;
    Cellule<T> * sentinelle;
    unsigned long taille;
public:
    Liste();
    ~Liste();
    bool est_vide();
    unsigned long nombre_element();
    Cellule<T> *  ajouter(Cellule<T> *);
    Cellule<T> * ajouter_trie(Cellule<T> *);
    Cellule<T> * ajouter_apres(Cellule<T>* , Cellule<T> *);
    Cellule<T> * ajouter_avant(Cellule<T>* , Cellule<T> *);
    int enlever(Cellule<T> v);
    Cellule<T> * recup_tete();
    Cellule<T> * recup_sentinelle();
    unsigned long recup_taille();
    void trier();
    Liste & operator= (const Liste &);
    void deplacer_avant(Cellule<T> *,Cellule<T> *);
};

template <class T> Liste<T> & Liste<T>::operator= (const Liste<T> & is){
    if(&is != this){
        taille = is.taille;
        Cellule<T> * p = is.tete;
        while (p!= is.sentinelle)
        {

            ajouter_trie(new Cellule<T>(p->get()));
            p = p->get_next();
        }
        
    }
    return * this;
};
template <class T> void Liste<T>::deplacer_avant(Cellule<T> * a,Cellule<T> * p){
    if(p == a)return;
    
    if(p == tete){
        a->get_prev()->next(a->get_next());
        a->get_next()->previous(a->get_prev());
        p->previous(a);
        a->next(p);
        tete = a;
    }else{
        if(a == tete){
            tete = tete->get_next();
        }else{
            a->get_prev()->next(a->get_next());
            a->get_next()->previous(a->get_prev());
        }
        
        p->get_prev()->next(a);
        a->previous(p->get_prev());
        p->previous(a);
        a->next(p);
        
    }        
};
template <class T> Liste<T>::Liste(){
    
    tete =  new Cellule<T> ;
    sentinelle = tete;
    taille = 0;
}; 
template <class T> Liste<T>::~Liste(){
   while(sentinelle!=tete){
       sentinelle = sentinelle->get_prev();
       delete sentinelle->get_next();
   }
   delete sentinelle;
};
template <class T> void Liste<T>::trier(){
    
    Cellule<T> * p  = tete;
    Cellule<T> * cur, * max;
    cur  = p;
    while ( cur != sentinelle)
    {   max = p;
        p = p->get_next();
        while ( p != sentinelle )
        {
            if(*max < *p){
                max = p;
            }
            p = p->get_next();
        }
        deplacer_avant(max,cur);
        cur = cur->get_next(); 
        p = cur;
    }
    

}; 
template <class T> Cellule<T> * Liste<T>::recup_tete(){
    return tete;
};
template <class T> Cellule<T> * Liste<T>::recup_sentinelle(){
    return sentinelle;
};
template <class T> unsigned long Liste<T>::recup_taille(){
    return taille;
};
template <class T> unsigned long Liste<T>::nombre_element(){
    return taille;
};
template <class T> bool Liste<T>::est_vide(){
    return taille == 0;
};
template <class T> Cellule<T> *  Liste<T>::ajouter(Cellule<T> * v){
    v->next(tete);
    tete->previous(v);
    tete = v;
    taille++;
    return v;
};
template <class T> Cellule<T> *  Liste<T>::ajouter_apres(Cellule<T> * v, Cellule<T> * a){
    
    v->get_next()->previous(a);
    a->next(v->get_next());
    v->next(a);
    a->previous(v);
    taille++;
    return v;
};
template <class T> Cellule<T> *  Liste<T>::ajouter_avant(Cellule<T>*  v, Cellule<T>  *a){
    if(v == tete){
        return ajouter(a);
    }
    
    v->get_prev()->next(a);
    
    a->previous(v->get_prev());
    v->previous(a);
    a->next(v);
    taille++;
    return v;
};
template <class T> Cellule<T> *  Liste<T>::ajouter_trie(Cellule<T> * a){
    if(taille == 0){
      return  ajouter(a);

        
    }
    Cellule<T> * b = tete;
    while ((*b)< (*a) && b!= sentinelle)
    {
        b = b->get_next();
    }
    return ajouter_avant(b,a);
};
template <class T> int Liste<T>::enlever(Cellule<T> v){
    if(taille == 0){
        return 1;
    }

    if(v.get() == tete->get() ){
        tete = v.get_next();
    }else{
       v.get_prev()->next(v.get_next());     
    }
    
    taille--;
    return 1;
};

#endif