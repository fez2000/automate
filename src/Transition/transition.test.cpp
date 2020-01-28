#include "Transition.hpp"
#include "../test/test.hpp"
#include "../Automate/Automate.hpp"
extern test::Test allTest;
std::string testName = "transition creation";
test::Rapport *testCreation(const test::TestValue *)
{

    automate::Transition *a = new automate::Transition();
    symbol on = 'a';
    automate::Transition *b = new automate::Transition(1, on, 2);
    return new test::Rapport(true, "test reussit");
};
std::string t = "determinisation";
test::Rapport *testDeterminidation(const test::TestValue *)
{
    automate::Automate b("ab");
    b.new_state(0);
    b.new_state(1);
    b.new_state(2);
    b.new_state(3);
    b.make_initiale(0);
    b.make_finale(3);
    b.set_trans(0, 'a', 0);
    b.set_trans(0, 'a', 1);
    b.set_trans(1, 'b', 2);
    b.set_trans(2, 'b', 3);
    b.print();
    b.determiniser();
    b.print();
    return new test::Rapport(true, "test reussit");
}
test::Rapport *testParse(const test::TestValue *)
{
    automate::Automate automaton;
    automaton.new_state();
    // automaton.print_states();
    return new test::Rapport(true, "test reussit");
}

test::UnitTest b(testName, testCreation);
test::UnitTest c(testName, testDeterminidation);
test::UnitTest d(testName, testParse);
void allTransitionUnit()
{
    addUnit(b);
    addUnit(c);
    addUnit(d);
}
