#ifndef PARSE_FROM_FILE
#define PARSE_FROM_FILE
#include "../Automate/Automate.hpp"

namespace lexique
{
//using token = strtok(line, ";");
class LexiqueAnalyser
{
private:
    std::map<std::string, automate::Automate> pile;

public:
    void addAutomate(char *name, automate::Automate a);
    void removeAutomate(char *name);
    bool check(char *word);
    void check(char *word, void (*func)(char *word, bool status));
    ~LexiqueAnalyser();
    LexiqueAnalyser();
};

LexiqueAnalyser::LexiqueAnalyser(/* args */)
{
}

LexiqueAnalyser::~LexiqueAnalyser()
{
}

}; // namespace lexique
#endif