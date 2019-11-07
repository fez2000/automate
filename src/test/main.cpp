#include <iostream>
#include "main.h"
#include <ctype.h>
#include <string.h>

void m(char *c){
      int i = 0;
      for ( i = 0; c[i] != '\0'; i++)
      {
            c[i] = toupper(c[i]);
      }
}
 
using namespace std;
int main(){

      char a[] ="zertty";

      
       m(a);
       cout<<a;
     return 0;
}