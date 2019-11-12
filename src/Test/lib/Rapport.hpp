#ifndef RAPPORT_H_INCLUDE
#define RAPPORT_H_INCLUDE
#include <iostream>
    namespace test{
        class Rapport
        {
        private:
            bool testStatus;
            std::string resumer; 
        public:
            Rapport(/* args */);
            void message(std::string);
            void message(const char *);
            std::string message();
            void status(bool);
            bool status();
            ~Rapport();
        };
                
    }
#endif