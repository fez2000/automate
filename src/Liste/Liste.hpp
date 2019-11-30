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
    Liste<T>(const Liste<T> &v);
    Liste();
    ~Liste();
    bool is_empty();
    unsigned long get_length();
    Liste<T> &add(Cellule<T> *);
    Liste<T> &push(Cellule<T> *);
    Liste<T> &add_sort(Cellule<T> *);
    Liste<T> &add_after(Cellule<T> *, Cellule<T> *);
    Liste<T> &add_before(Cellule<T> *, Cellule<T> *);
    long get_index_of(T);
    int remove(Cellule<T> v);
    int removeByValue(T v);
    Cellule<T> *get_head();
    Cellule<T> *get_sentries();
    Cellule<T> *get_head() const;
    Cellule<T> *get_sentries() const;
    void sort();
    void clear();
    bool has_value(const T &);
    Liste<T> &operator=(const Liste<T> &);
    friend Liste<T> operator+(Liste<T> d, Liste<T> s)
    {
        std::cout << "add\n";
        Cellule<T> *p = s.get_head();
        while (p != s.get_sentries())
        {
            std::cout << "add\n";
            d.add_sort(new Cellule<T>(p->val()));
            p = p->next();
        }

        return d;
    };
    friend bool operator==(const Liste<T> &l1, const Liste<T> &l2)
    {
        if (l1.length != l2.length)
            return false;
        Cellule<T> *p = l2.head;
        while (p != l2.sentries)
        {
            bool b = false;
            Cellule<T> *p2 = NULL;
            p2 = l1.head;
            while (p2 != l1.sentries)
            {
                if (p2->val() == p->val())
                {
                    b = true;
                }
                p2 = p2->next();
            }

            if (!b)
            {
                return false;
            }
            p = p->next();
        }

        return true;
    };
    void move_before(Cellule<T> *, Cellule<T> *);
};
template <class T>
Cellule<T> *Liste<T>::get_head() const
{
    return head;
};
template <class T>
Cellule<T> *Liste<T>::get_sentries() const
{
    return sentries;
};
template <class T>
bool Liste<T>::has_value(const T &s)
{
    Cellule<T> *p = NULL;
    p = this->head;
    while (p != this->sentries)
    {
        if (p->val() == s)
        {
            return true;
        }
        p = p->next();
    }
    return false;
};
template <class T>
long Liste<T>::get_index_of(T v)
{
    Cellule<T> *p = NULL;
    p = this->head;
    long index = -1, i = 0;
    while (p != this->sentries)
    {
        if (p->val() == v)
        {
            index = i;
            break;
        }
        p = p->next();
        i++;
    }
    return index;
};
template <class T>
Liste<T>::Liste(const Liste<T> &is)
{
    head = new Cellule<T>;
    sentries = head;
    length = is.length;
    Cellule<T> *p = is.head;
    while (p != is.sentries)
    {

        push(new Cellule<T>(p->val()));
        p = p->next();
    }
};
template <class T>
Liste<T> &Liste<T>::operator=(const Liste<T> &is)
{
    if (&is != this)
    {
        clear();
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
        head = head->next();

        delete head->prev();
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
Liste<T> &Liste<T>::push(Cellule<T> *v)
{
    if (length == 0)
    {
        return add(v);
    }
    add_before(v, sentries);

    return *this;
};
template <class T>
Liste<T> &Liste<T>::add(Cellule<T> *v)
{
    v->next(head);
    head->prev(v);
    head = v;
    length++;
    return *this;
};
template <class T>
Liste<T> &Liste<T>::add_after(Cellule<T> *v, Cellule<T> *a)
{

    v->next()->prev(a);
    a->next(v->next());
    v->next(a);
    a->prev(v);
    length++;
    return *this;
};
template <class T>
Liste<T> &Liste<T>::add_before(Cellule<T> *v, Cellule<T> *a)
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
    return *this;
};
template <class T>
Liste<T> &Liste<T>::add_sort(Cellule<T> *a)
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