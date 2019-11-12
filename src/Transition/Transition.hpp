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
        void to(state);
        void from(state);
    };
    

    
};
#endif