#ifndef CELLULE_H_INCLUDE
#define CELLULE_H_INCLUDE
#include <fstream>
template <class T>
class Cellule
{
protected:
    T valeur;
    Cellule<T> *precedent, *suivant;

public:
    void prev(Cellule<T> *);
    void next(Cellule<T> *);
    void val(T);
    T val();
    Cellule<T> *prev();
    Cellule<T> *next();
    Cellule();
    Cellule(T);
    ~Cellule();
    Cellule<T> &operator=(const Cellule<T> &);
    friend int operator==(const Cellule<T> &c1, const Cellule<T> &c2)
    {
        return c1.val() == c2.val();
    };
    friend int operator<(Cellule<T> c1, Cellule<T> c2)
    {
        return c1.val() < c2.val();
    };
    friend int operator<=(Cellule<T> c1, Cellule<T> c2)
    {
        return c1.val() <= c2.val();
    };
    friend int operator>(const Cellule<T> &c1, const Cellule<T> &c2)
    {
        return c1.val() > c2.val();
    };
    friend std::ostream &operator<<(std::ostream &os, const Cellule<T> &b)
    {

        os << b.valeur;
        return os;
    };
    friend std::istream &operator>>(std::istream &os, Cellule<T> &b)
    {
        if (!os)
            return os;
        os >> b.valeur;
        return os;
    };
};
#include "Cellule.hpp"
#include "stdlib.h"
#include <fstream>

template <class T>
void Cellule<T>::val(T val)
{
    valeur = val;
}
template <class T>
void Cellule<T>::next(Cellule<T> *n)
{
    suivant = n;
}
template <class T>
void Cellule<T>::prev(Cellule<T> *p)
{
    precedent = p;
}
template <class T>
T Cellule<T>::val()
{
    return valeur;
}
template <class T>
Cellule<T> *Cellule<T>::next()
{
    return suivant;
}
template <class T>
Cellule<T> *Cellule<T>::prev()
{
    return precedent;
}

template <class T>
Cellule<T>::Cellule()
{
    precedent = suivant = NULL;
}

template <class T>
Cellule<T>::Cellule(T val)
{
    precedent = suivant = NULL;
    valeur = val;
};
template <class T>
Cellule<T>::~Cellule(){};
template <class T>
Cellule<T> &Cellule<T>::operator=(const Cellule<T> &c)
{
    if (&c != this)
    {
        valeur = c.valeur;
    }
    return *this;
};

#endif
