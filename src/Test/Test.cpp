#include "Test.hpp"

namespace test {
    Test::Test(/* args */)
    {
    }
    
    Test::~Test()
    {
    }
    void Test::addUnit(UnitTest u){
      this->units.ajouter( new Cellule<UnitTest>(u));  
    };
    void Test::make(){
        Cellule<UnitTest> * p;
        p = units.recup_tete();
        while(p != units.recup_sentinelle()){
            
            p->val().makeTest(&allValue);
      
            p = p->next();
        }
    };
}