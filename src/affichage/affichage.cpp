#include "affichage.hpp"
// variables globales

std::string choixUtilisateur;
/*
    Acceuil
*/
void acceuil(){

    // differentes variables a utiliser dans notre fonction
    int i = charger("fr");//position a changer
    std::string choixValide("012345");
    do{
        
        // petit menu de presentation
        std::cout << "\t\033[36;1m##############################################################################################################\n";            
        std::cout << "\t##-_-_-                                                                                                -_-_-##\n";
        std::cout << "\t##\033[36;0m                           \033[33;1mBIENVENUE DANS LE LOGICIEL DE GESTION DU SUPERMARCHE\033[33;0m                           \033[36;1m##\n";
        std::cout << "\t##                                                                                                          ##\n";
        std::cout << "\t##                          ---------------------------------------------------                             ##\n";
        std::cout << "\t##                          ---------------------------------------------------                             ##\n";
        std::cout << "\t##\033[36;0m                                         \033[33;1m%%%     %%%     %%%\033[33;0m                                              \033[36;1m##\n";
        std::cout << "\t##\033[36;0m                                          \033[33;1m%%%   %%%      %%%\033[33;0m                                              \033[36;1m##\n";
        std::cout << "\t##\033[36;0m                                            \033[33;1m%%%%%        %%%\033[33;0m                                              \033[36;1m##\n";
        std::cout << "\t##\033[36;0m                                            \033[33;1m%%%%%        %%%\033[33;0m                                              \033[36;1m##\n";
        std::cout << "\t##\033[36;0m                                          \033[33;1m%%%   %%%      %%%%%%%%%%\033[33;0m                                       \033[36;1m##\n";
        std::cout << "\t##\033[36;0m                                         \033[33;1m%%%     %%%     %%%%%%%%%%\033[33;0m                                       \033[36;1m##\n";
        std::cout << "\t##                          ---------------------------------------------------                             ##\n";
        std::cout << "\t##                          ---------------------------------------------------                             ##\n";
        std::cout << "\t##\033[36;0m                              \033[32;1mVeuillez suivre à la lettre les consigne !\033[32;0m                                  \033[36;1m##\n";
        std::cout << "\t##                          ---------------------------------------------------                             ##\n";
        std::cout << "\t##\033[36;0m      \033[33;1mTapez:\033[33;0m                                                                                              \033[36;1m##\n";
        std::cout << "\t##\033[36;0m          \033[33;1m1- Pour GESTIONS CLIENTS                         2- Pour GESTIONS ARTICLES\033[33;0m                      \033[36;1m##\n";
        std::cout << "\t##\033[36;0m          \033[33;1m3- Pour GESTIONS COMMANDES                       4- Pour GESTIONS LIVRAISONS\033[33;0m                    \033[36;1m##\n";
        std::cout << "\t##\033[36;0m          \033[33;1m5- Pour AUTRES FONCTIONS                         0- QUITTER\033[33;0m                                     \033[36;1m##\n";
        std::cout << "\t##-_-_-                                                                                                -_-_-##\n";
        std::cout << "\t##     -----------------------------------------------------------------------------------------------      ##\n";
        std::cout << "\t##                                                                                                          ##\n";

        std::cout << "\t##\033[36;0m \033[33;1mEntrer votre choix:\033[33;0m \t";
        std::cin >> choixUtilisateur;
        system("clear");

    } while (choix_non_valide(choixUtilisateur,choixValide));


    switch (choixUtilisateur.c_str()[0]){
        case '0':
            exit(0);
        break;
      
    };
}






