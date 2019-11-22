#include "main.hpp"
#include <string>

using namespace std;
int main()
{

     automate::Automate a;
     symbol b = 'a';
     a.new_state(1);
     a.new_state(2);

     a.set_trans(1, b, 2);
     a.set_trans(2, b, 1);
     a.make_initiale(1);
     a.make_finale(2);

     if (a.belongs("aaaa"))
     {
          cout << " trur\n";
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