#ifndef AFFICHAGE_H_INCLUDE
#define AFFICHAGE_H_INCLUDE
#include "../fonctions/fonctions.hpp"
#include "../Automate/Automate.hpp"
void acceuil(); // fonction qui affiche le menu d'acceuil
void gestion_automates();
void liste_automates();
void changer_automate();
void entrez_automate();
void modifier_automate(automate::Automate *a);
void afficher_automate(automate::Automate *a);
#endif