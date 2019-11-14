#include "../test/test.hpp"

test::Test allTest;
void addUnit(test::UnitTest a){
    allTest.addUnit(a);
}
void startTest(){
    allTransitionUnit();
    allTest.make();
}