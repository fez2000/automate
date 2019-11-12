#ifndef TYPE_H_INCLUDE
#define TYPE_H_INCLUDE
#include <stdlib.h>
#include <iostream>
typedef int state;
typedef  union  {
    char c, *s = NULL;
} symbol;
  
enum Mois { JANVIER, FEVRIER, MARS, AVRIL, MAI, JUIN, JUILLET, AOUT, SEPTEMBRE, OCTOBRE, NOVEMBRE, DECEMBRE };
enum  { PAS_DERREUR, PAS_TROUVER, PAS_UN_NOMBRE, ID_INVALID, ERREUR_FIC_LANG , ERREUR_SYSTEME };
typedef unsigned long typeId;
typedef long long typeQte;


#endif