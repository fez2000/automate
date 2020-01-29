#ifndef PARSE_FROM_FILE
#define PARSE_FROM_FILE
#include "../Automate/Automate.hpp"
#define TOK_BUFSIZE 512
#define TOK_DELIM " "
namespace lexique
{

class Analyser
{
private:
    std::map<std::string, automate::Automate> pile;

public:
    void addAutomate(const char *name, automate::Automate a);
    void removeAutomate(const char *name);
    bool check(const char *word);
    void check(const char *word, void (*func)(char *word, bool status));
    static std::vector<std::string> split(char *, const char *);
    ~Analyser();
    Analyser();
};

}; // namespace lexique
#endif