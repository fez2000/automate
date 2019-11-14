#ifndef LISTE_H_INCLUDE
#define LISTE_H_INCLUDE
#include "../Cellule/Cellule.hpp"
#include <iostream>
#include <fstream>
template <class T>
class Liste
{
protected:
    Cellule<T> *head;
    Cellule<T> *sentries;
    unsigned long length;

public:
    Liste();
    ~Liste();
    bool is_empty();
    unsigned long get_length();
    Cellule<T> *add(Cellule<T> *);
    Cellule<T> *add_sort(Cellule<T> *);
    Cellule<T> *add_after(Cellule<T> *, Cellule<T> *);
    Cellule<T> *add_before(Cellule<T> *, Cellule<T> *);
    int remove(Cellule<T> v);
    int removeByValue(T v);
    Cellule<T> *get_head();
    Cellule<T> *get_sentries();
    void sort();
    void clear();
    Liste &operator=(const Liste &);
    void move_before(Cellule<T> *, Cellule<T> *);
};

template <class T>
Liste<T> &Liste<T>::operator=(const Liste<T> &is)
{
    if (&is != this)
    {
        length = is.length;
        Cellule<T> *p = is.head;
        while (p != is.sentries)
        {

            add_sort(new Cellule<T>(p->val()));
            p = p->next();
        }
    }
    return *this;
};
template <class T>
void Liste<T>::move_before(Cellule<T> *a, Cellule<T> *p)
{
    if (p == a)
        return;

    if (p == head)
    {
        a->prev()->next(a->next());
        a->next()->prev(a->prev());
        p->prev(a);
        a->next(p);
        head = a;
    }
    else
    {
        if (a == head)
        {
            head = head->next();
        }
        else
        {
            a->prev()->next(a->next());
            a->next()->prev(a->prev());
        }

        p->prev()->next(a);
        a->prev(p->prev());
        p->prev(a);
        a->next(p);
    }
};
template <class T>
Liste<T>::Liste()
{

    head = new Cellule<T>;
    sentries = head;
    length = 0;
};
template <class T>
Liste<T>::~Liste()
{
    clear();
    delete sentries;
};
template <class T>
void Liste<T>::clear()
{
    while (sentries != head)
    {
        sentries = sentries->prev();
        delete sentries->next();
    }
    length = 0;
}
template <class T>
void Liste<T>::sort()
{

    Cellule<T> *p = head;
    Cellule<T> *cur, *max;
    cur = p;
    while (cur != sentries)
    {
        max = p;
        p = p->next();
        while (p != sentries)
        {
            if (*max < *p)
            {
                max = p;
            }
            p = p->next();
        }
        move_before(max, cur);
        cur = cur->next();
        p = cur;
    }
};
template <class T>
Cellule<T> *Liste<T>::get_head()
{
    return head;
};
template <class T>
Cellule<T> *Liste<T>::get_sentries()
{
    return sentries;
};
template <class T>
unsigned long Liste<T>::get_length()
{
    return length;
};

template <class T>
bool Liste<T>::is_empty()
{
    return length == 0;
};
template <class T>
Cellule<T> *Liste<T>::add(Cellule<T> *v)
{
    v->next(head);
    head->prev(v);
    head = v;
    length++;
    return v;
};
template <class T>
Cellule<T> *Liste<T>::add_after(Cellule<T> *v, Cellule<T> *a)
{

    v->next()->prev(a);
    a->next(v->next());
    v->next(a);
    a->prev(v);
    length++;
    return v;
};
template <class T>
Cellule<T> *Liste<T>::add_before(Cellule<T> *v, Cellule<T> *a)
{
    if (v == head)
    {
        return add(a);
    }

    v->prev()->next(a);

    a->prev(v->prev());
    v->prev(a);
    a->next(v);
    length++;
    return v;
};
template <class T>
Cellule<T> *Liste<T>::add_sort(Cellule<T> *a)
{
    if (length == 0)
    {
        return add(a);
    }
    Cellule<T> *b = head;
    while ((*b) < (*a) && b != sentries)
    {
        b = b->next();
    }
    return add_before(b, a);
};
template <class T>
int Liste<T>::remove(Cellule<T> v)
{
    if (length == 0)
    {
        return 1;
    }

    if (v.get() == head->get())
    {
        head = v.next();
    }
    else
    {
        v.prev()->next(v.next());
    }

    length--;
    return 1;
};
template <class T>
int Liste<T>::removeByValue(T v)
{
    if (length == 0)
    {
        return 1;
    }
    Cellule<T> *p = head;
    size_t j = 0;
    while (p != sentries)
    {

        if (p->val() == v)
        {

            if (j == 0)
            {

                head = p->next();
                delete p;
                p = head;

                continue;
            }
            else
            {

                p->prev()->next(p->next());
                Cellule<T> *a = p;
                p = p->next();
                delete a;
            }
        }
        p = p->next();
        j++;
    }

    length--;
    return 1;
};

#endif