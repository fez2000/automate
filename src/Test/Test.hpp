#ifndef TEST_H_INCLUDE
#define TEST_H_INCLUDE
#include "../fonctions/fonctions.hpp"
#include "./lib/UnitTest.hpp"
#include "../Liste/Liste.hpp"
namespace test{
    
    

    class Test
    {
    private:
        Liste<UnitTest> units;
    public:
        Test(/* args */);
        ~Test();
    };
    
    Test::Test(/* args */)
    {
    }
    
    Test::~Test()
    {
    }
    
    
    
    
    
};
#endif