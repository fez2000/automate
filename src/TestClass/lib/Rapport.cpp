#include "Rapport.hpp"

namespace test {
        Rapport::Rapport(/* args */)
        {
        }
        Rapport::Rapport(bool t, const char * m)
        {
            resumer.assign(m);
            testStatus = t;
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
        void Rapport::message(std::string m){
            resumer = m;
        };
        void Rapport::status(bool t){
            testStatus = t;
        };
        bool Rapport::status(){
            return testStatus;
        };
}