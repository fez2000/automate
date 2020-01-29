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
    std::cout << "Les etats sont: " << b.print_states_str() << "\n";
    std::cout << "Les etats Initiaux: " << b.print_states_initial_str() << "\n";
    std::cout << "Les etats finaux: " << b.print_states_finale_str() << "\n";
    std::cout << "l'alphabet: " << b.print_alphabet_str() << "\n";
    std::cout << "graphe des transition: " << b.print_str() << "\n";
    return new test::Rapport(true, "test reussit");
}
test::UnitTest b(testName, testCreation);
test::UnitTest c(testName, testDeterminidation);
void allTransitionUnit()
{
    addUnit(b);
    addUnit(c);
}
