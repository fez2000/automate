#include "main.hpp"
#include <string>

using namespace std;
int main()
{

     automate::Automate a;
     symbol b = 'a';
     a.new_state(2);
     cout << "hum\n";
     a.set_trans(1, b, 2);
     cout << "hum\n";
     a.del_trans_on(1, b);
     char i = -127;
     string d = "";
     while (i < 126)
     {
          cout << i;
          i++;
     }
     cout << "\n";
}