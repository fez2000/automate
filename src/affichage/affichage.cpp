#include "affichage.hpp"
// variables globales
std::map<std::string, automate::Automate *> all;
std::map<std::string, automate::Automate *>::iterator current = all.end();
std::string choixUtilisateur;
/*
    Acceuil
*/
void acceuil()
{

    // differentes variables a utiliser dans notre fonction
    int i = charger("fr"); //position a changer
    std::string choixValide("123");
    do
    {
        system("clear");
        // petit menu de presentation
        std::cout << " bienvenue dans le devoir de fezeu ghomisi eugene clotaire 17Q2864\n\n";
        std::cout << " 1) gestion de mes automates \n";
        std::cout << " 2) operations sur mes automates \n";
        std::cout << " 3) quitter\n";
        getline(std::cin, choixUtilisateur);
        system("clear");

    } while (choix_non_valide(choixUtilisateur, choixValide));

    switch (choixUtilisateur.c_str()[0])
    {
    case '1':
        gestion_automates();
        acceuil();
        break;
    case '2':
    case '3':
        exit(0);
        break;
    };
}

void gestion_automates()
{
    std::string choixValide("012345");
    do
    {

        // petit menu de presentation
        std::cout << " 0) retourner au menu\n";
        std::cout << " 1) liste des automates \n";
        std::cout << " 2) changer d'automate courant \n";
        std::cout << " 3) entrez un automate\n";
        std::cout << " 4) afficher\n";
        std::cout << " 5) quitter\n";
        getline(std::cin, choixUtilisateur);
        system("clear");
    } while (choix_non_valide(choixUtilisateur, choixValide));

    switch (choixUtilisateur.c_str()[0])
    {
    case '0':
        acceuil();
        break;
    case '1':
        liste_automates();
        gestion_automates();
    case '2':
        changer_automate();
        gestion_automates();
        break;
    case '3':
        entrez_automate();
        gestion_automates();
        break;
    case '4':
        if (current != all.end())
            afficher_automate((*current).second);
        gestion_automates();
        break;
    default:
        break;
    };
}

void afficher_automate(automate::Automate *a)
{
    if (a)
    {

        std::cout << "Les etats sont: " << a->print_states_str() << "\n";
        std::cout << "Les etats Initiaux: " << a->print_states_initial_str() << "\n";
        std::cout << "Les etats finaux: " << a->print_states_finale_str() << "\n";
        std::cout << "l'alphabet: " << a->print_alphabet_str() << "\n";
        std::cout << "graphe des transition: " << a->print_str() << "\n";
    }
    else
    {
        std::cout << "pas d'automate a afficher\n";
    }
    getline(std::cin, choixUtilisateur);
}
void liste_automates()
{
    std::map<std::string, automate::Automate *>::iterator p = all.begin();
    int i = 1;
    std::cout << "  LISTE DES AUTOMATES: \n";
    while (p != all.end())
    {
        std::cout << i++ << ")  " << (*p).first << "\n";
        p++;
    }
    std::cout << "\n";
}

void changer_automate()
{
    if (all.size() == 0)
    {
        std::cout << "automates insuffisant pour faire une selection \n";
        return;
    }
    std::string nom;
    do
    {
        std::cout << "stop pour tout arreter\nle nom de l'automate  ";
        getline(std::cin, nom);
    } while (all.find(nom) == all.end() && (nom.compare("stop") != 0));
    if (nom.compare("stop") == 0)
        return;
    current = all.find(nom);
}
void entrez_automate()
{
    std::string nom;
    do
    {
        std::cout << "stop pour tout arreter\nle nom de l'automate  ";
        getline(std::cin, nom);
    } while (nom.size() == 0 && (nom.compare("stop") != 0));
    if (nom.compare("stop") == 0)
        return;
    std::string choixValide("12");
    do
    {
        std::cout << "1) choisir l'aphabet par defaut. il est constituer de tous les caracteres imprimable\n";
        std::cout << "2) entrer l'alphabet\n";
        getline(std::cin, choixUtilisateur);
    } while (choix_non_valide(choixUtilisateur, choixValide));
    switch (choixUtilisateur.c_str()[0])
    {
    case '1':
        all[nom] = new automate::Automate();
        if (all.size() == 1)
            current = all.begin();
        break;
    case '2':
        std::string alphabet;
        std::cout << " l'alphabet: ";
        getline(std::cin, alphabet);
        all[nom] = new automate::Automate(alphabet.c_str());
        modifier_automate(all[nom]);
        break;
    }
}
void modifier_automate(automate::Automate *a)
{
    std::string choixValide("123456");
    std::string nombre, nombre2, etats = a->print_states_str(), etasInitiaux = a->print_states_initial_str(), etatsFinales = a->print_states_finale_str();
    long nb;
    state e1, e2;
    symbol s;
    do
    {
        std::cout << "1) Ajouter un etat\n";
        std::cout << "2) Ajouter un etat initiale\n";
        std::cout << "3) Ajouter un etat finale\n";
        std::cout << "4) Ajouter n etat \n";
        std::cout << "5) Ajouter une transition\n";
        std::cout << "6) Arreter\n";
        getline(std::cin, choixUtilisateur);
    } while (choix_non_valide(choixUtilisateur, choixValide));
    switch (choixUtilisateur.c_str()[0])
    {
    case '1':
        do
        {
            std::cout << "Entrez votre etat ";
            getline(std::cin, nombre);
            nb = convertion1(nombre.c_str());
        } while (nb == -1);
        a->new_state(nb);
        modifier_automate(a);
        break;
    case '2':
        do
        {
            std::cout << "Entrez votre etat ";
            getline(std::cin, nombre);
            nb = convertion1(nombre.c_str());
        } while (nb == -1);
        a->new_state(nb);
        a->make_initiale(nb);
        modifier_automate(a);
        break;
    case '3':
        do
        {
            std::cout << "Entrez votre etat ";
            getline(std::cin, nombre);
            nb = convertion1(nombre.c_str());
        } while (nb == -1);
        a->new_state(nb);
        a->make_finale(nb);
        modifier_automate(a);
        break;
    case '4':
        do
        {
            std::cout << "Entrez le nombre d'etat ";
            getline(std::cin, nombre);
            nb = convertion1(nombre.c_str());
        } while (nb == -1);
        while (nb > 0)
        {
            a->new_state();
            nb--;
        }

        modifier_automate(a);
        break;
    case '5':
        etats = a->print_states_str(), etasInitiaux = a->print_states_initial_str(), etatsFinales = a->print_states_finale_str();
        std::cout << "Les etats sont: " << etats << "\n";
        std::cout << "Les etats Initiaux: " << etasInitiaux << "\n";
        std::cout << "Les etats finaux: " << etatsFinales << "\n";
        std::cout << "l'alphabet: " << a->print_alphabet_str() << "\n";
        do
        {
            std::cout << "Entrez votre etat source ";
            getline(std::cin, nombre);
            e1 = convertion1(nombre.c_str());
            if (!a->is_state(e1))
            {
                std::cout << "Entrez un etat valide\n";
                continue;
            }
        } while (e1 == -1 || !a->is_state(e1));
        do
        {
            std::cout << "Entrez votre etat destination ";
            getline(std::cin, nombre2);
            e2 = convertion1(nombre2.c_str());
            if (!a->is_state(e2))
            {
                std::cout << "Entrez un etat valide\n";
                continue;
            }
        } while (e2 == -1 || !a->is_state(e2));
        do
        {
            std::cout << "Entrez votre etat symbol(ecrire espillon en toute lettre ou juste le symbol) ";
            getline(std::cin, nombre);
            if (nombre.compare("espillon") == 0)
            {
                s = '\0';
                break;
            }
            else
            {
                if (nombre.size() > 0)
                {
                    if (!a->check_symbol(nombre.c_str()[0]))
                    {
                        std::cout << "Entrez un symbol de l'alphabet\n";
                        continue;
                    }
                    s = nombre.c_str()[0];
                }
            }

        } while (nombre.size() == 0 || (nombre.compare("espillon") != 0) && (!a->check_symbol(nombre.c_str()[0])));
        a->set_trans(e1, s, e2);
        modifier_automate(a);
        break;
    default:
        break;
    }
}