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
std::string status_of(automate::Automate *a);
void afficher_status();
void reconnaissance_mot();
void operations_automates();
void intersection_of_automates();
void union_of_automates();
void sup_epsillon_transition();
void determiniser_automate();
void transformer_afd_afn();
void completer();
void automate_miroir();
void sup_unuse();
#endif