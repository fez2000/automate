#include "UnitTest.hpp"

namespace test{
    UnitTest::UnitTest()
    {
         
    }
     UnitTest::UnitTest( std::string name)
    {
        this->UnitTestName = name;
    }
    UnitTest::UnitTest( std::string name, Rapport * (* testFunction)( const TestValue * ) )
    {
        this->UnitTestName = name;
        this->testFunction = testFunction;
        
    }
    UnitTest::UnitTest( Rapport * (* testFunction)( const TestValue * ) )
    {
        this->testFunction = testFunction;
    }  
    UnitTest::~UnitTest()
    {
        if(testFeetBack){
            delete(testFeetBack);
        };
        
    }

    void UnitTest::testOn(Rapport * (* testFunction)( const TestValue * ) ){
        this->testFunction = testFunction;
      
    };
    void UnitTest::displayRapport(){
        if(testFeetBack ){
            std::cout << UnitTestName << std::endl << testFeetBack->message() << std::endl;
        }
    };
   
    Rapport * UnitTest::makeTest(const TestValue * v){
        Rapport * p = NULL,* e = NULL;
        try {
            e =  testFunction(v);
            p = new Rapport(*e);
            delete e;
        } catch (const std::overflow_error& e) {
            // this executes if f() throws std::overflow_error (same type rule)
             std::cout << e.what();
             p = new Rapport();
             p->message(e.what());
             p->status(false); 
        } catch (const std::runtime_error& e) {
            // this executes if f() throws std::underflow_error (base class rule)
             std::cout << e.what(); 
             p = new Rapport();
             p->message(e.what());
             p->status(false);
        } catch (const std::exception& e) {
            // this executes if f() throws std::logic_error (base class rule)
             std::cout << e.what(); 
             p = new Rapport();
             p->message(e.what());
             p->status(false);
        } catch (...) {
            // this executes if f() throws std::string or int or any other unrelated type
            
            p = new Rapport();
            p->message("dsds");
            p->status(false);
        }
        return p;
    };
}