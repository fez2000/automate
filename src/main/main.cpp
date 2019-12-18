#include "main.hpp"
#include <string>

using namespace std;
int main()
{

     automate::Automate a("ab");
     automate::Automate b("ab");

     a.new_state(1);
     a.new_state(2);
     a.new_state(3);
     a.set_trans(1, 'a', 2);
     a.set_trans(2, 'a', 1);
     a.set_trans(2, 'b', 3);
     a.set_trans(2, '\0', 3);
     a.set_trans(3, 'a', 1);
     a.make_initiale(3);
     a.make_initiale(1);
     a.make_finale(2);
     b.new_state(1);
     b.new_state(2);
     b.new_state(3);
     b.set_trans(1, 'b', 2);
     b.set_trans(2, 'b', 1);
     b.set_trans(2, 'a', 3);
     b.set_trans(2, '\0', 3);
     b.set_trans(3, 'a', 1);
     b.make_initiale(3);
     b.make_initiale(1);
     b.make_finale(2);
     a.print();
     if (a.has_epsilon_transition())
     {
          std::cout << "with epsillon\n";
          a.print();
     }
     if (a.is_deterministe())
     {
          std::cout << "c'est deterministe\n";
     }
     a.remove_epsilon_transition();
     b.remove_epsilon_transition();
     if (a.has_epsilon_transition())
     {
          std::cout << "with epsillon\n";
          a.print();
     }
     b.make_full();
     a.make_full();
     a.print();
     a.duplicate_state(3);
     a.print();
     a.determiniser();
     b.determiniser();
     a.print();
     a.print_states_finale();
     a.print_states_initial();
     if (a.belongs("aaa"))
     {
          cout << " trur\n";
     }
     else
     {
          cout << "false \n";
     }
     a.determiniser();
     a.print();
     a.print_states_finale();
     a.print_states_initial();
     a.print_alphabet();

     std::cout << "what\n";
     if (a.belongs("aaa"))
     {
          cout << " trur\n";
     }
     else
     {
          cout << "false \n";
     }
     if (a.is_full())
     {
          cout << "True\n";
     }
     if (a.accessible(3))
     {
          cout << "accessible\n";
     }
     char i = -127;
     string d = "";
     while (i < 126)
     {
          cout << i;
          i++;
     }
     cout << "\n";
     automate::Automate *c = automate::unionof_closing(a, b);
     c->print();
     //delete c;
     cout << "end\n";
}