#ifndef TRANSITION_H_INCLUDE
#define TRANSITION_H_INCLUDE
#include "../fonctions/fonctions.hpp"
namespace automate{
    class Transition
    {
    private:
       state source, destination;
       symbol a;
    public:
        Transition(/* args */);
        Transition( state from, symbol on, state to);
        ~Transition();
        state to();
        state from();
        symbol on();

        void on(symbol);
        void to(state);
        void from(state);
        Transition& operator= (const Transition &);
        friend int operator== (Transition  c1,Transition  c2);
        friend int operator< (Transition  c1,Transition  c2);
        friend int operator<= ( Transition  c1, Transition  c2);
        friend int operator> (const Transition & c1,const Transition & c2);
    };
    

    
};
#endif