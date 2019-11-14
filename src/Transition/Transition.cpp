#include "Transition.hpp"
#include <string.h>
namespace automate
{
Transition::Transition(/* args */)
{
    source = destination = 0;
}

Transition &Transition::operator=(const Transition &is)
{
    if (&is != this)
    {
        a = is.a;
        source = is.source;
        destination = is.destination;
    }
    return *this;
};
Transition::~Transition()
{
}
int operator==(Transition c1, Transition c2)
{

    return c1.source == c2.source && c1.destination == c2.destination && c1.a == c2.a;
};
int operator<(Transition c1, Transition c2)
{
    return c1.source < c2.source;
};
int operator<=(Transition c1, Transition c2)
{
    return c1.source <= c2.source;
};
int operator>(const Transition &c1, const Transition &c2)
{
    return c1.source > c2.source;
};
Transition::Transition(state from, symbol on, state to)
{
    source = from;
    a = on;
    destination = to;
};
state Transition::to()
{
    return destination;
};
state Transition::from()
{
    return source;
};
void Transition::to(state to)
{
    destination = to;
};
void Transition::from(state from)
{
    source = from;
};
symbol Transition::on()
{
    return a;
};

void Transition::on(symbol s)
{
    a = s;
};
} // namespace automate
