#ifndef AUTOMATE_H_INCLUDE
#define AUTOMATE_H_INCLUDE
#include "../fonctions/fonctions.hpp"
#include "../Erreur/Erreur.hpp"
#include "../Transition/Transition.hpp"
#include "../Liste/Liste.hpp"
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <string>
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
    std::vector<std::vector<std::set<symbol> *> > graphe;
    std::set<state> etatsFinaux;
    std::set<state> etatsInitaux;
    std::set<state> etats;
    void remove_line(size_t i);
    void remove_col_on_line(size_t j, size_t i);
    state _new_state();
    void print_set_of_state(const std::set<state> &);
    std::set<state> epsilon_closing(state e, std::set<state> &see);
    std::set<state> transit(state e, symbol a, std::set<state> &see);

public:
    // Ajouts/suppression
    void remove_epsilon_transition();
    bool has_epsilon_transition(state e);
    state new_state();
    void duplicate_state(state e, state to);
    state duplicate_state(state e);
    void print_states_finale();
    void print_states_initial();
    void new_state(state);
    void set_trans(state from, symbol a, state to);
    void del_trans(state source);
    void del_trans_on(state source, symbol a);
    void del_trans_on_to(state source, symbol a, state destination);
    void del_trans_all_to(state destination);
    bool is_full();
    void make_full();
    void del_state(state s);
    void print();
    // Modification
    //void initial(state s);
    //virtual bool calcul(const symbol *mot);
    std::set<state> epsilon_closing(state e);
    std::set<state> epsilon_closing(std::set<state> s);
    std::set<state> transit(state e, symbol a);
    std::set<state> transit(std::set<state> e, symbol a);

    void copy_state(state from, state to);
    void change_trans(state s, symbol a, state new_aim);
    void init_sigma(const symbol *);
    void append_state(state s);
    void make_finale(state s);
    void make_initiale(state s);
    void print_alphabet();
    void remove_state(state s);
    void remove_state_finale(state s);
    void remove_state_initiale(state s);
    bool is_finale(state s);
    bool is_finale(const std::set<state> &s);
    bool is_initiale(state s);
    bool belongs(const symbol *word);
    bool check_symbols(const symbol *word);
    bool check_symbol(symbol word);
    bool accessible(state e);
    bool coaccessible(state s);
    bool useful(state s);
    bool is_trim_automaton();
    void determiniser();
    bool reachEnd(state current, std::set<state> &see);
    bool reach(state current, state dest, std::set<state> &see);
    bool calculate_word_at(const symbol *word, state start);
    std::set<state>
    next_state_on(state s, symbol a);
    std::set<state>
    next_state_on(std::set<state> s, symbol a);
    std::set<state>
    next_state_on(state s);
    Automate(/* args */);
    Automate(const char *alphabet);
    ~Automate();
};

}; // namespace automate
#endif
