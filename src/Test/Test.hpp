#ifndef TEST_H_INCLUDE
#define TEST_H_INCLUDE
#include "../fonctions/fonctions.hpp"
#include "./lib/UnitTest.hpp"
#include "../Liste/Liste.hpp"
#include "./lib/TestValue.hpp"

namespace test{
    
    

    class Test
    {
    private:
        Liste<UnitTest> units;
        TestValue allValue;
    public:
        Test(/* args */);
        void addUnit(UnitTest);
        void make();
        ~Test();
    };
    
    
    
    
    
    
    
};
#endif