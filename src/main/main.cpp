#include "main.hpp"
#include <string>

using namespace std;
int main()
{

     automate::Automate a("ab");
     a.print_alphabet();
     symbol b = 'a';
     a.new_state(1);
     a.new_state(2);
     a.new_state(3);
     a.set_trans(1, b, 2);
     a.set_trans(2, b, 1);
     a.set_trans(2, 'b', 3);
     a.set_trans(3, 'b', 2);
     a.set_trans(3, 'a', 1);
     a.make_initiale(3);
     a.make_initiale(1);
     a.make_finale(2);
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
}