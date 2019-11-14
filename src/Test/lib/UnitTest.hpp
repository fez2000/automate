#ifndef UNITTEST_H_INCLUDE
#define UNITTEST_H_INCLUDE
#include "../../type.hpp"
#include "TestValue.hpp"
#include <string>
#include "Rapport.hpp"
#include <exception>
#include <typeinfo>
#include <stdexcept>


    namespace test{
        class UnitTest 
        {
        private:

            Rapport * testFeetBack;
            Rapport * (* testFunction)( const TestValue * );
            std::string UnitTestName;
        public:
            UnitTest(/* args */);
            UnitTest(std::string UnitTestName);
            UnitTest(Rapport * (* testFunction)( const TestValue * ));
            UnitTest(std::string UnitTestName, Rapport * (* testFunction)( const TestValue * ));
            ~UnitTest();
            void testOn(Rapport * (* testFunction)( const TestValue * ));
            void displayRapport();
            void displayName();
            Rapport * makeTest(const TestValue *);
        };
        

    }
#endif