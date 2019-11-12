#include "Rapport.hpp"

namespace test {
        Rapport::Rapport(/* args */)
        {
        }
        
        Rapport::~Rapport()
        {
        }
        std::string Rapport::message(){
            return resumer;
        };
        void Rapport::message(const char * m){
            resumer.assign(m);
        };
        void Rapport::status(bool t){
            testStatus = t;
        };
        bool Rapport::status(){
            return testStatus;
        };
}