#ifndef AUTOMATE_H_INCLUDE
#define AUTOMATE_H_INCLUDE
#include "../fonctions/fonctions.hpp"
#include "../Transition/Transition.hpp"
#include "../Liste/Liste.hpp"
#include <set>
#include <vector>

    namespace automate{
        /**
         * @name: Automate
         * @description: class de base des automate
         * @attr:
         *  -sigma l'ensemble des symbol
         *  
         */
        class Automate
        {
        protected:
            std::set<symbol> sigma;
            std::vector< std::vector< Liste<Transition>>> graphe;
            Liste<state> etatsFinaux;
            Liste<state> etatsInitaux;
            Liste<state> etats;  
        public:
            // Ajouts/suppression
            state new_state();
            void set_trans(state from, symbol a, state to);
            void del_trans(state s, symbol a);
            state duplicate_state(state s);
            void del_state(state s);
            // Modification
            //void initial(state s);
            void copy_state(state from, state to);
            void change_trans(state s, symbol a, state new_aim);
            Automate(/* args */);
            ~Automate();
        };
        
        Automate::Automate(/* args */)
        {
        }
        
        Automate::~Automate()
        {
        }
        
    };
#endif