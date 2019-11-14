#include "Transition.hpp"
#include "../test/test.hpp"

extern test::Test allTest;
std::string testName = "transition creation";
test::Rapport *testCreation(const test::TestValue *)
{

    automate::Transition *a = new automate::Transition();
    symbol on = 'a';
    automate::Transition *b = new automate::Transition(1, on, 2);
    return new test::Rapport(true, "test reussit");
};

test::UnitTest b(testName, testCreation);
void allTransitionUnit()
{
    addUnit(b);
}
