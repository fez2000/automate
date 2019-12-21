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
        std::cout << " Bienvenue dans le devoir de fezeu ghomisi eugene clotaire 17Q2864\n\n";
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
        operations_automates();
        acceuil();
        break;
    case '3':
        exit(0);
        break;
    };
}

void gestion_automates()
{
    std::string choixValide("0123456");
    system("clear");
    do
    {

        // petit menu de presentation
        std::cout << " 0) retourner au menu\n";
        std::cout << " 1) liste des automates \n";
        std::cout << " 2) changer d'automate courant \n";
        std::cout << " 3) entrez un automate\n";
        std::cout << " 4) afficher\n";
        std::cout << " 5) avoir le status de l'automate courant\n";
        std::cout << " 6) modifier l'automate courant\n";
        //std::cout << " 7) quitter\n";
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
        {
            afficher_automate(current->second);
        }
        else
        {
            std::cout << "veuillez choisir un automate courant ";
            getline(std::cin, choixUtilisateur);
        }

        gestion_automates();
        break;
    case '5':
        afficher_status();
        gestion_automates();
        break;
    case '6':
        if (current != all.end())
        {
            modifier_automate(current->second);
        }
        else
        {
            std::cout << "veuillez choisir un automate courant ";
            getline(std::cin, choixUtilisateur);
        }

        gestion_automates();
        break;

    default:
        break;
    };
}

std::string status_of(automate::Automate *a)
{
    std::stringstream out;

    if (a->has_epsilon_transition())
    {
        out << "est un epsillon-";
    }
    else
    {
        out << "est un ";
    }
    if (a->is_deterministe())
    {
        out << "automate fini deterministe";
    }
    else
    {
        out << "automate fini non deterministe";
    }
    if (a->is_full())
    {
        out << " complet";
    }
    else
    {
        out << " non complet";
    }
    if (a->is_trim_automaton())
    {
        out << " et emonde";
    }
    else
    {
        out << " et pas emonde";
    }
    out << "\n";
    return out.str();
}
void afficher_status()
{
    if (current != all.end())
    {
        std::cout << current->first << ": " << status_of(current->second);
    }
    else
    {
        std::cout << "veuillez choisir un automate courant ";
    }
    getline(std::cin, choixUtilisateur);
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
    getline(std::cin, choixUtilisateur);
}

void changer_automate()
{
    if (all.size() == 0)
    {
        std::cout << "automates insuffisant pour faire une selection \n";
        return;
    }

    std::string nom, method, choixValide("123");
    do
    {
        std::cout << "1) entrer le nom l'automate\n";
        std::cout << "2) entrer le numero de l'automate\n";
        std::cout << "3) tout arreter ";
        getline(std::cin, choixUtilisateur);
    } while (choix_non_valide(choixUtilisateur, choixValide));
    switch (choixUtilisateur.c_str()[0])
    {
    case '1':
        do
        {
            std::cout << "stop pour tout arreter\nle nom de l'automate  ";
            getline(std::cin, nom);
        } while (all.find(nom) == all.end() && (nom.compare("stop") != 0));
        if (nom.compare("stop") == 0)
            return;
        current = all.find(nom);
        break;

    case '2':
        do
        {
            std::cout << "stop pour tout arreter\nle numero de l'automate  ";
            getline(std::cin, choixUtilisateur);
        } while (convertion1(choixUtilisateur.c_str()) == -1 && (choixUtilisateur.compare("stop") != 0));
        if (choixUtilisateur.compare("stop") == 0)
            return;
        int i = convertion1(choixUtilisateur.c_str());
        if (i > all.size() || i < 1)
        {
            std::cout << "Indice hors de l'intervale de valeurs valides\n";
            getline(std::cin, choixUtilisateur);
        }
        else
        {
            current = all.begin();
            i--;
            while (i > 0)
            {
                current++;
                i--;
            }
        }

        break;
    }
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
    std::string choixValide("1234"), choixValide2("12345");
    std::string nombre, nombre2, etats = a->print_states_str(), etasInitiaux = a->print_states_initial_str(), etatsFinales = a->print_states_finale_str();
    long nb;
    state e1, e2;
    symbol s;
    do
    {
        /*std::cout << "1) Ajouter un etat\n";
        std::cout << "2) Ajouter un etat initiale\n";
        std::cout << "3) Ajouter un etat finale\n";
        std::cout << "5) Ajouter une transition\n";
        std::cout << "6) Arreter\n";*/
        std::cout << "1) Faire un ajout\n";
        std::cout << "2) Faire une suppression\n";
        std::cout << "3) Ajouter n etat \n";
        std::cout << "4) Quitter \n";
        getline(std::cin, choixUtilisateur);
    } while (choix_non_valide(choixUtilisateur, choixValide));
    switch (choixUtilisateur.c_str()[0])
    {
    case '1':
        do
        {
            std::cout << "1) Ajouter un etat\n";
            std::cout << "2) Ajouter un etat initiale\n";
            std::cout << "3) Ajouter un etat finale\n";
            std::cout << "4) Ajouter une transition\n";
            std::cout << "5) quitter\n";
            getline(std::cin, choixUtilisateur);
        } while (choix_non_valide(choixUtilisateur, choixValide2));
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
            modifier_automate(a);
            break;
        }

        break;
    case '2':
        do
        {
            std::cout << "1) Supprimer un etat\n";
            std::cout << "2) Supprimer un etat initiale\n";
            std::cout << "3) Supprimer un etat finale\n";
            std::cout << "4) Supprimer une transition\n";
            std::cout << "5) quitter\n";
            getline(std::cin, choixUtilisateur);
        } while (choix_non_valide(choixUtilisateur, choixValide2));
        switch (choixUtilisateur.c_str()[0])
        {
        case '1':
            do
            {

                std::cout << "Entrez votre etat ";
                getline(std::cin, nombre);
                nb = convertion1(nombre.c_str());
            } while (nb == -1);
            a->remove_state(nb);
            modifier_automate(a);
            break;
        case '2':
            do
            {
                std::cout << "Entrez votre etat ";
                getline(std::cin, nombre);
                nb = convertion1(nombre.c_str());
            } while (nb == -1);

            a->remove_state_initiale(nb);
            modifier_automate(a);
            break;
        case '3':
            do
            {
                std::cout << "Entrez votre etat ";
                getline(std::cin, nombre);
                nb = convertion1(nombre.c_str());
            } while (nb == -1);
            a->remove_state_finale(nb);
            modifier_automate(a);
            break;
        case '4':
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
            a->del_trans_on_to(e1, s, e2);

            modifier_automate(a);
            break;
        default:
            modifier_automate(a);
            break;
        }

        break;
    case '3':
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

    default:
        break;
    }
}
void operations_automates()
{
    int choix;

    do
    {
        system("clear");
        std::cout << "1)    Liste des automates\n";
        std::cout << "2)    Changer l'automate courant\n";
        std::cout << "3)    Faire la reconnaissance d'un mot\n";
        std::cout << "4)    L'union de deux automates deterministe \n";
        std::cout << "5)    L'intersection de deux automates deterministe \n";
        std::cout << "6)    L'espillon fermeture \n";
        std::cout << "7)    Calculer l'automate miroire \n";
        std::cout << "9)    Rendre l'automate complet \n";
        std::cout << "10)   Determiniser \n";
        std::cout << "11)   Status de l'automate\n";
        std::cout << "12)   Supprimer  les epsillons transitions\n";
        std::cout << "13)   Transformer un afd en afn \n";
        std::cout << "14)   Suppression des etats inutiles, non accessible ou pas co-accessible \n";
        std::cout << "15)   Afficher \n";
        std::cout << "16)   Calculer le complementaire \n";
        std::cout << "17)   Standardiser un afn\n";
        std::cout << "18)   Cloture par etoille\n";
        std::cout << "19)   dupliquer\n";
        getline(std::cin, choixUtilisateur);
        system("clear");
        choix = convertion1(choixUtilisateur.c_str());
    } while (choix < 0);
    switch (choix)
    {
    case 1:
        liste_automates();
        operations_automates();
        break;
    case 2:
        changer_automate();
        operations_automates();
        break;
    case 3:
        reconnaissance_mot();
        operations_automates();

        break;
    case 4:
        union_of_automates();
        operations_automates();
        break;
    case 5:
        intersection_of_automates();
        operations_automates();
        break;
    case 6:
        automate_miroir();
        operations_automates();
        break;
    case 7:
        if (current != all.end())
        {
            state a;
            do
            {
                std::cout << " Etats " << current->second->print_states_str() << " stop pour arreter : ";
                getline(std::cin, choixUtilisateur);
                if (choixUtilisateur.compare("stop") == 0)
                    return;
                a = convertion1(choixUtilisateur.c_str());
            } while (a == -1 || !current->second->is_state(a));
            std::cout << current->second->print_set_of_state_str(current->second->epsilon_closing(a)) << "\n";
            getline(std::cin, choixUtilisateur);
        }
        else
        {
            std::cout << "veillez choisir un automate courant\n";
            getline(std::cin, choixUtilisateur);
        }
        operations_automates();
        break;
    case 9:
        completer();
        operations_automates();
        break;
    case 10:
        determiniser_automate();
        operations_automates();
        break;
    case 11:
        afficher_status();
        operations_automates();
        break;
    case 12:
        sup_epsillon_transition();
        operations_automates();
        break;
    case 13:
        transformer_afd_afn();
        operations_automates();
        break;
    case 14:
        sup_unuse();
        operations_automates();
        break;
    case 15:
        if (current != all.end())
        {
            afficher_automate(current->second);
        }
        else
        {
            std::cout << "veillez choisir un automate courant\n";
            getline(std::cin, choixUtilisateur);
        }
        operations_automates();
        break;
    case 16:
        if (current != all.end())
        {
            current->second->complementary();
        }
        else
        {
            std::cout << "veillez choisir un automate courant\n";
            getline(std::cin, choixUtilisateur);
        }
        operations_automates();
        break;
    case 17:
        if (current != all.end())
        {
            std::string nom;
            do
            {
                std::cout << "Entrez le nom du resultat ";
                getline(std::cin, nom);
            } while (nom.size() == 0);
            all[nom] = new automate::Automate(*current->second);
            all[nom]->standardisation();
        }
        else
        {
            std::cout << "veillez choisir un automate courant\n";
            getline(std::cin, choixUtilisateur);
        }
        operations_automates();
        break;
    case 18:
        if (current != all.end())
        {
            std::string nom;
            do
            {
                std::cout << "Entrez le nom du resultat ";
                getline(std::cin, nom);
            } while (nom.size() == 0);

            all[nom] = automate::etoile_closing(*current->second);
        }
        else
        {
            std::cout << "veillez choisir un automate courant\n";
            getline(std::cin, choixUtilisateur);
        }
        operations_automates();
        break;
    case 19:
        if (current != all.end())
        {
            std::string nom;
            do
            {
                std::cout << "Entrez le nom du resultat ";
                getline(std::cin, nom);
            } while (nom.size() == 0);
            all[nom] = new automate::Automate(*current->second);
        }
        else
        {
            std::cout << "veillez choisir un automate courant\n";
            getline(std::cin, choixUtilisateur);
        }
        operations_automates();
        break;
    default:
        break;
    }
}
void automate_miroir()
{
    if (current != all.end())
    {
        std::string nom;
        do
        {
            std::cout << "Entrez le nom de l'automte ";
            getline(std::cin, nom);
        } while (nom.size() == 0);
        automate::Automate *b = new automate::Automate(*current->second);
        b->miroir();
        all[nom] = b;
    }
    else
    {
        std::cout << "veillez choisir un automate courant\n";
        getline(std::cin, choixUtilisateur);
    }
}
void sup_epsillon_transition()
{
    if (current != all.end())
    {
        if (!current->second->has_epsilon_transition())
        {
            std::cout << "L'automate " << current->first << "n'as pas d'espillon transition\n";
            getline(std::cin, choixUtilisateur);
        }
        else
        {
            std::string choixValide("12");
            do
            {
                std::cout << "1) Enlever toutes les epsillons transitions pour chaque etat\n";
                std::cout << "2) Enlever toutes les epsillons transitions pour un etat\n";
                getline(std::cin, choixUtilisateur);
            } while (choix_non_valide(choixUtilisateur, choixValide));
            switch (choixUtilisateur.c_str()[0])
            {
            case '1':
                current->second->remove_epsilon_transition();
                break;
            case '2':
                state a;
                do
                {
                    std::cout << " Etats " << current->second->print_states_str() << " stop pour arreter : ";
                    getline(std::cin, choixUtilisateur);
                    if (choixUtilisateur.compare("stop") == 0)
                        return;
                    a = convertion1(choixUtilisateur.c_str());
                } while (a == -1 || !current->second->is_state(a));
                current->second->remove_epsilon_transition(a);
                break;
            default:
                break;
            }
        }
    }
    else
    {
        std::cout << "veillez choisir un automate courant\n";
        getline(std::cin, choixUtilisateur);
    }
}
void determiniser_automate()
{
    if (current != all.end())
    {
        if (current->second->is_deterministe())
        {
            std::cout << "L'automate " << current->first << "est deja deterministe\n";
            getline(std::cin, choixUtilisateur);
        }
        else
        {
            if (current->second->has_epsilon_transition())
                current->second->remove_epsilon_transition();
            current->second->determiniser();
        }
    }
    else
    {
        std::cout << "veillez choisir un automate courant\n";
        getline(std::cin, choixUtilisateur);
    }
}
void completer()
{
    if (current != all.end())
    {
        current->second->make_full();
    }
    else
    {
        std::cout << "veillez choisir un automate courant\n";
        getline(std::cin, choixUtilisateur);
    }
}
void transformer_afd_afn()
{
    if (current != all.end())
    {
        if (!current->second->is_deterministe())
        {
            std::cout << "L'automate " << current->first << "est deja non deterministe\n";
            getline(std::cin, choixUtilisateur);
        }
        else
        {
            std::set<state> be = current->second->states();
            if (be.size() == 0)
            {
                if (current->second->is_finale(*be.begin()) && current->second->is_initiale(*be.begin()))
                {
                    state a = current->second->duplicate_state(*be.begin());
                    current->second->make_finale(a);
                    current->second->make_initiale(a);
                }
                else
                {
                    if (current->second->is_finale(*be.begin()))
                    {
                        state a = current->second->duplicate_state(*be.begin());
                        current->second->make_finale(a);
                    }
                    else
                    {
                        state a = current->second->duplicate_state(*be.begin());
                        current->second->make_initiale(a);
                    }
                }
            }
        }
    }
    else
    {
        std::cout << "veillez choisir un automate courant\n";
        getline(std::cin, choixUtilisateur);
    }
}
void reconnaissance_mot()
{
    if (current != all.end())
    {
        std::string mot;
        std::cout << "Entrez le mot a reconnaitre par l'automate " << current->first << ": ";
        getline(std::cin, mot);
        try
        {
            if (current->second->belongs(mot.c_str()))
            {
                std::cout << "Le mot " << mot << " est reconnu par l'automate " << current->first << "\n";
            }
            else
            {
                std::cout << "Le mot " << mot << "n'est pas reconnu par l'automate " << current->first << "\n";
            }
        }
        catch (my_exception *e)
        {
            std::cout << e->what() << "\n";
        }
        catch (...)
        {
        }
        std::cout << "Voulez vous recommencer ? oui(o)/non(n) ";
        getline(std::cin, mot);
        if (mot.compare("oui") == 0 || mot.compare("o") == 0)
        {
            reconnaissance_mot();
        }
    }
    else
    {
        std::cout << "veuillez choisir un automate courant ";
        getline(std::cin, choixUtilisateur);
    }
}
void union_of_automates()
{
    if (all.size() < 2)
    {
        std::cout << "Automate insuffisant pour faire l'union\n";
        getline(std::cin, choixUtilisateur);
        return;
    }
    int nombre_deterministe = 0, i = 0;
    std::map<std::string, automate::Automate *>::iterator il = all.begin();
    std::cout << "List Automate deterministe: \n";

    while (il != all.end())
    {

        if (il->second->is_deterministe())
        {
            std::cout << ++i << ")  " << il->first << "\n";
            nombre_deterministe++;
        }
        else
        {
            i++;
        }
        il++;
    }

    if (nombre_deterministe < 2)
    {
        std::cout << "Automate insuffisant pour faire l'union\n";
    }
    std::string nom1, nom2, result;
    do
    {
        std::cout << "Le nom du premier automate ou stop pour arreter: ";
        getline(std::cin, nom1);
        if (nom1.compare("stop") == 0)
            return;
        if (!all[nom1]->is_deterministe())
        {
            std::cout << "l'automate dois etre deterministe\n";
        }
        if (!all[nom1]->is_full())
        {
            std::cout << "l'automate dois etre complet\n";
        }
    } while (!all[nom1] || !all[nom1]->is_full() || !all[nom1]->is_deterministe());
    do
    {
        std::cout << "Le nom du deuxieme automate ou stop pour arreter: ";
        getline(std::cin, nom2);
        if (nom2.compare("stop") == 0)
            return;
        if (!all[nom2]->is_deterministe())
        {
            std::cout << "l'automate dois etre deterministe\n";
        }
        if (!all[nom2]->is_full())
        {
            std::cout << "l'automate dois etre complet\n";
        }
    } while (!all[nom2] || !all[nom1]->is_full() || !all[nom2]->is_deterministe());
    if (!automate::has_equal_sigma(*all[nom2], *all[nom1]))
    {
        std::cout << "les sigmas sont differents\n";
        getline(std::cin, choixUtilisateur);
        return;
    }
    std::cout << "Le nom du resultat \n";
    do
    {
        getline(std::cin, result);
    } while (result.size() == 0);
    all[result] = automate::unionof_closing(*all[nom1], *all[nom2]);
}
void intersection_of_automates()
{
    if (all.size() < 2)
    {
        std::cout << "Automate insuffisant pour faire l'intersection\n";
        getline(std::cin, choixUtilisateur);
        return;
    }
    int nombre_deterministe = 0, i = 0;
    std::map<std::string, automate::Automate *>::iterator il = all.begin();
    std::cout << "List Automate deterministe: \n";

    while (il != all.end())
    {

        if (il->second->is_deterministe())
        {
            std::cout << ++i << ")  " << il->first;
            nombre_deterministe++;
        }
        else
        {
            i++;
        }
        il++;
    }
    if (nombre_deterministe < 2)
    {
        std::cout << "Automate insuffisant pour faire l'intersection\n";
    }
    std::string nom1, nom2, result;
    do
    {
        std::cout << "Le nom du premier automate ou stop pour arreter: ";
        getline(std::cin, nom1);
        if (nom1.compare("stop") == 0)
            return;
        if (!all[nom1]->is_deterministe())
        {
            std::cout << "l'automate dois etre deterministe\n";
        }
        if (!all[nom1]->is_full())
        {
            std::cout << "l'automate dois etre complet\n";
        }
    } while (!all[nom1] || !all[nom1]->is_deterministe() || !all[nom1]->is_full());
    do
    {
        std::cout << "Le nom du deuxieme automate ou stop pour arreter: ";
        getline(std::cin, nom2);
        if (nom2.compare("stop") == 0)
            return;
        if (!all[nom2]->is_deterministe())
        {
            std::cout << "l'automate dois etre deterministe\n";
        }
        if (!all[nom2]->is_full())
        {
            std::cout << "l'automate dois etre complet\n";
        }
    } while (!all[nom2] || !all[nom2]->is_deterministe() || !all[nom2]->is_full());
    if (!automate::has_equal_sigma(*all[nom2], *all[nom1]))
    {
        std::cout << "les sigmas sont differents\n";
        getline(std::cin, choixUtilisateur);
        return;
    }
    std::cout << "Le nom du resultat \n";
    do
    {
        getline(std::cin, result);
    } while (result.size() == 0);
    all[result] = automate::unionof_closing(*all[nom1], *all[nom2]);
}
void sup_unuse()
{
    if (current != all.end())
    {
        std::string choixValide("1234");
        do
        {
            std::cout << "1)    Etats inutiles\n";
            std::cout << "2)    Etats non accessible\n";
            std::cout << "3)    Etats pas co-accessible\n";
            std::cout << "4)    Annuler \n";
            getline(std::cin, choixUtilisateur);
        } while (choix_non_valide(choixUtilisateur, choixValide));
        std::set<state> be;
        std::set<state>::iterator il;
        switch (choixUtilisateur.c_str()[0])
        {
        case '1':
            be = current->second->states();
            il = be.begin();
            while (il != be.end())
            {
                if (!current->second->useful(*il))
                    current->second->remove_state(*il);
                il++;
            }

            break;
        case '2':
            be = current->second->states();
            il = be.begin();
            while (il != be.end())
            {
                if (!current->second->accessible(*il))
                    current->second->remove_state(*il);
                il++;
            }

            break;
        case '3':
            be = current->second->states();
            il = be.begin();
            while (il != be.end())
            {
                if (!current->second->coaccessible(*il))
                    current->second->remove_state(*il);
                il++;
            }

            break;
        default:
            break;
        }
    }
    else
    {
        std::cout << "veillez choisir un automate courant\n";
        getline(std::cin, choixUtilisateur);
    }
}