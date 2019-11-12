#include "Transition.hpp"

namespace automate {
    Transition::Transition(/* args */)
    {
        source = destination = 0;
    }
    
    Transition::~Transition()
    {
        if(a.s){
            cfree(a.s);
        }
    }
    Transition::Transition( state from, symbol on, state to){
        source = from;
        a.c = on.c;
        a.s = on.s;
        destination = to;
    };
    state Transition::to(){
        return destination;
    };
    state Transition::from(){
        return source;
    };
    void Transition::to(state to){
        destination = to;
    };
    void Transition::from(state from){
        source = from;
    };
}
    