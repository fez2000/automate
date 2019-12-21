#ifndef FONCTIONS_H_INCLUDE
#define FONCTIONS_H_INCLUDE
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstdarg>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include "../lang/lang.hpp"
#include "../type.hpp"
#define ERROR_CODE 0
#define SUCCESS_CODE 1
#define MAX 500
#define TAB "\t"

//types definition
template <typename T>
std::string to_str(T nombre)
{
    std::stringstream strs;
    strs << nombre;
    std::string g(strs.str().c_str());
    return g;
};
void get_str(char *, const char *);
long double get_long_double(char *chaine, const char *msa);
long long get_long(char *chaine, const char *msg);
long double convertion2(char *chaine);
long convertion1(const char *chaine);
std::string cat_many(int, ...);
bool est_premier(long);
long prochain_nb_premier(long);
bool choix_non_valide(std::string choix, std::string listeValide);
bool is_sexe(const char *);

std::ostream &serialiser(std::ostream &os, const std::string &s);
std::istream &deserialiser(std::istream &is, std::string &s);
bool is_affirmatif(const char *);
long long de_string_pour_long_long(std::string s);
typeId convertion(const char *chaine);
std::string majuscule(const char *);
std::string majuscule(std::string);
void set_insert(std::set<symbol> &d, const std::set<symbol> &s);
void set_insert(std::set<state> &d, const std::set<state> &s);
bool are_equal_set(const std::set<state> &s1, const std::set<state> &s2);
bool are_equal_set(std::set<symbol> &s1, std::set<symbol> &s2);

#endif