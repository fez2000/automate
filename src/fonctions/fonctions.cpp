#include <iomanip>
#include <iostream>
#include "fonctions.hpp"
#include <math.h>
#include <string.h>
#include <vector>
#include <fstream>

void get_str(char *mot, const char *msg)
{
    do
    {
        std::cout << msg;
        std::cin.getline(mot, MAX);
    } while (strlen(mot) == 0);
};
long long get_long(char *chaine, const char *msg)
{
    long long v;
    std::cin.clear();
    do
    {
        std::cout << msg;
        std::cin.getline(chaine, MAX);
        v = convertion1(chaine);
    } while (v < 0);
    return v;
}
long double get_long_double(char *chaine, const char *msg)
{
    long double v;
    std::cin.clear();
    do
    {
        std::cout << msg;
        std::cin.getline(chaine, MAX);
        v = convertion2(chaine);
    } while (v < 0);
    return v;
}
long double convertion2(char *chaine)
{
    unsigned i = 0;
    long double nombre = 0;
    long double finNombre = 0;
    int x1 = 10, x2 = 0.1;
    while (chaine[i] != '\0')
    {

        if (chaine[i] > 47 && chaine[i] < 59)
        {
            nombre = nombre * x1 + chaine[i] - 48;
        }
        else
        {
            if (!(chaine[i] == ',' || chaine[i] == '.'))
            {
                return -1;
            }
        }
        i++;
    }
    while (chaine[i] != '\0')
    {

        if (chaine[i] > 47 && chaine[i] < 59)
        {
            finNombre = finNombre * x2 + chaine[i] - 48;
        }
        else
        {

            return -1;
        }
        i++;
    }
    return nombre + finNombre;
};
std::string majuscule(const char *m)
{
    size_t n = strlen(m), i = 0;
    std::string r;
    while (i < n)
    {
        r.push_back(std::toupper(m[i]));
        i++;
    }
    return r;
};
std::string majuscule(std::string m)
{
    return majuscule(m.c_str());
};
bool choix_non_valide(std::string choix, std::string listeValide)
{
    long i = listeValide.size();
    if (choix.size() > 1)
        return true;
    while (--i >= 0)
    {
        if (choix[0] == listeValide[i])
        {
            return false;
        }
    }
    return true;
};
bool is_sexe(const char *s)
{
    if (strlen(s) > 1)
        return false;
    if (s[0] == 'F' || s[0] == 'M')
        return true;
    return false;
};
long long de_string_pour_long_long(std::string s)
{
    long long num = 0;
    long long i = 0, N = s.size();

    while (i < N)
    {
        num = s[i] * i + num;
        i++;
    }
    return num;
}

bool est_premier(long p)
{
    if (p <= 1)
    {
        return false;
    }
    int i = 2;
    long g = sqrtf(p);
    while (i <= g)
    {
        if (p % i == 0)
        {
            return false;
        }
        i++;
    }
    return true;
}
long prochain_nb_premier(long p)
{
    while (!est_premier(++p))
        ;
    return p;
}
bool is_affirmatif(const char *choix)
{
    int i = 0;
    std::vector<const char *> Choix;
    Choix.push_back("OUI");
    Choix.push_back("O");
    Choix.push_back("YES");
    Choix.push_back("Y");
    Choix.push_back("oui");
    Choix.push_back("o");
    Choix.push_back("yes");
    Choix.push_back("y");
    while (i < 8)
    {
        if (strcmp(choix, Choix[i]) == 0)
        {
            return true;
        }
        i++;
    }
    return false;
};
void set_insert(std::set<symbol> &d, const std::set<symbol> &s)
{
    std::set<symbol>::iterator il = s.begin();
    while (il != s.end())
    {
        d.insert(*il);
        il++;
    }
};
void set_insert(std::set<state> &d, const std::set<state> &s)
{
    std::set<state>::iterator il = s.begin();
    while (il != s.end())
    {
        d.insert(*il);
        il++;
    }
};
std::ostream &serialiser(std::ostream &os, const std::string &s)
{
    return os << '\"' << s << '\"';
}
std::istream &deserialiser(std::istream &is, std::string &s)
{
    if (!is)
        return is;
    char c;
    if (is >> c && c != '\"')
    {
        is.putback(c);
        // mettre is en état d'erreur
        return is;
    }
    std::string temp;
    while (is >> c && c != '\"')
        temp += c;
    if (is) // ou if ( == '\"') au choix
        s = temp;
    return is;
};
/*
    @brief cat_many cat str argument in to one string 
    @params nbCh number of char * passed 
    @return a string resulting of concatanation off all char * parsed
    */
std::string cat_many(int nbCh, ...)
{
    va_list liste;
    va_start(liste, nbCh);
    int i;
    std::string reslut;
    for (i = 1; i <= nbCh; i++)
    {
        std::string tampon = va_arg(liste, char *);
        reslut += tampon;
    }
    va_end(liste);

    return reslut;
}
long convertion1(const char *chaine)
{
    unsigned i = 0;
    long nombre = 0;

    while (chaine[i] != '\0')
    {

        if (chaine[i] > 47 && chaine[i] < 59)
        {
            nombre = nombre * 10 + chaine[i] - 48;
        }
        else
        {
            return -1;
        }
        i++;
    }

    return nombre;
}
typeId convertion(char *chaine)
{
    unsigned i = 0;
    typeId nombre = 0;

    while (chaine[i] != '\0')
    {

        if (chaine[i] > 47 && chaine[i] < 59)
        {

            nombre = nombre * 10 * i + chaine[i] - 48;
        }
        else
        {
            return ERROR_CODE;
        }
        i++;
    }
    return nombre;
}
bool are_equal_set(const std::set<state> &s1, const std::set<state> &s2)
{
    std::set<state>::iterator il;
    il = s1.begin();
    while (il != s1.end())
    {
        if (s2.find(*il) == s2.end())
            return false;
        il++;
    }

    return s1.size() == s2.size();
};
bool are_equal_set(std::set<symbol> &s1, std::set<symbol> &s2)
{
    std::set<symbol>::iterator il;
    il = s1.begin();
    while (il != s1.end())
    {
        if (s2.find(*il) == s2.end())
            return false;
        il++;
    }
    return true;
};