#include "Transition.hpp"

void testCreation(){
    automate::Transition * a = new automate::Transition();
    symbol on = {
        c: 'a',
    };
    automate::Transition * b = new automate::Transition(1,on,2);
}