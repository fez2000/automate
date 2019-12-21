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
    std::set<symbol> get_sigma();
    // Ajouts/suppression
    void remove_epsilon_transition();
    bool has_epsilon_transition(state e);
    state new_state();
    void duplicate_state(state e, state to);
    state duplicate_state(state e);
    void print_states();
    void print_states_finale();
    void print_states_initial();
    void new_state(state);
    void set_trans(state from, symbol a, state to);
    void del_trans(state source);
    void del_trans_on(state source, symbol a);
    void del_trans_on_to(state source, symbol a, state destination);
    void del_trans_all_to(state destination);
    bool is_full();
    bool is_deterministe();
    void make_full();
    void del_state(state s);
    void print();
    std::string print_str();
    void print_alphabet();
    std::string print_alphabet_str();
    std::string print_set_of_state_str(const std::set<state> &s);
    std::string print_states_initial_str();
    std::string print_states_finale_str();
    std::string print_states_str();
    // Modification
    //void initial(state s);
    //virtual bool calcul(const symbol *mot);
    //pour les clotures les alphabets doivent avoir le ensemble des symbol sigma et etre deterministe
    friend Automate *unionof_closing(Automate a1, Automate a2);
    friend Automate *intersection_closing(Automate a1, Automate a2);
    friend Automate miroir_closing(Automate a1, Automate a2);
    friend Automate *concatenation_closing(Automate a1, Automate a2);
    friend Automate *etoile_closing(Automate a1, Automate a2);
    friend Automate *opt_plus(Automate a1, Automate a2);
    friend Automate *opt_concat(Automate a1, Automate a2);
    friend Automate *opt_etoille(Automate a1, Automate a2);
    std::set<state> epsilon_closing(state e);
    std::set<state> epsilon_closing(std::set<state> s);
    std::set<state> transit(state e, symbol a);
    std::set<state> transit(std::set<state> e, symbol a);
    bool has_epsilon_transition();
    void copy_state(state from, state to);
    void change_trans(state s, symbol a, state new_aim);
    void init_sigma(const symbol *);
    void append_state(state s);
    void make_finale(state s);
    void make_initiale(state s);

    void remove_state(state s);
    void remove_state_finale(state s);
    void remove_state_initiale(state s);
    void complementary();
    void miroir();
    bool is_state(state s);
    bool is_finale(state s);
    bool is_finale(const std::set<state> &s);
    bool is_initiale(state s);
    bool is_initiale(const std::set<state> &s);
    bool belongs(const symbol *word);
    bool check_symbols(const symbol *word);
    bool check_symbol(symbol word);
    bool accessible(state e);   // dit si un etat est accessible
    bool coaccessible(state s); // dit si un etat est coaccessible
    bool useful(state s);       // dit si un etat est complet
    bool is_trim_automaton();   // dit si un automate est emonde

    void determiniser();
    void standardisation();
    void remove_epsilon_transition(state e);
    bool reachEnd(state current, std::set<state> &see);
    bool reach(state current, state dest, std::set<state> &see);
    bool calculate_word_at(const symbol *word, state start);
    std::set<state>
    next_state_on(state s, symbol a);
    std::set<state>
    next_state_on(std::set<state> s, symbol a);
    std::set<state>
    next_state_on(state s);
    void etoile_closing();
    Automate(/* args */);
    Automate(const char *alphabet);
    Automate(std::set<symbol>);
    ~Automate();
    std::set<state> states();
    std::set<state> states_initial();
    std::set<state> states_finale();
    friend bool has_equal_sigma(Automate &a1, Automate &a2);
};
bool has_equal_sigma(Automate &a1, Automate &a2);
Automate *unionof_closing(Automate a1, Automate a2);
Automate *intersection_closing(Automate a1, Automate a2);
Automate *opt_plus(Automate a1, Automate a2);
Automate *opt_concat(Automate a1, Automate a2);
Automate *opt_etoille(Automate a1, Automate a2);
Automate *concatenation_closing(Automate a1, Automate a2);
Automate *etoile_closing(Automate a1);
}; // namespace automate
#endif
