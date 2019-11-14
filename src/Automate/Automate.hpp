#ifndef AUTOMATE_H_INCLUDE
#define AUTOMATE_H_INCLUDE
#include "../fonctions/fonctions.hpp"
#include "../Transition/Transition.hpp"
#include "../Liste/Liste.hpp"
#include <set>
#include <vector>
#define EPSILONE '\0'
#define MOTVIDE NULL
#define DEFAULT_ALPHABET "!\"#$%&'()*+,./123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}"

namespace automate
{
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
    std::vector<std::vector<Liste<symbol> *> > graphe;
    Liste<state> etatsFinaux;
    Liste<state> etatsInitaux;
    Liste<state> etats;
    void remove_line(size_t i);
    void remove_col_on_line(size_t j, size_t i);
    state _new_state();

public:
    // Ajouts/suppression
    state new_state();
    void new_state(state);
    void set_trans(state from, symbol a, state to);
    void del_trans(state source);
    void del_trans_on(state source, symbol a);
    void del_trans_on_to(state source, symbol a, state destination);
    void del_trans_all_to(state destination);
    bool is_full();
    state duplicate_state(state s);
    void del_state(state s);
    // Modification
    //void initial(state s);
    //virtual bool calcul(const symbol *mot);
    void copy_state(state from, state to);
    void change_trans(state s, symbol a, state new_aim);
    void init_sigma(const symbol *);
    Automate(/* args */);
    ~Automate();
};

}; // namespace automate
#endif
