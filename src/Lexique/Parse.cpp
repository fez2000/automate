#include "Parse.hpp"
#include <string>
#include <iostream>

namespace lexique
{
using namespace std;
std::vector<std::string> Analyser::split(char *line, const char *delimiter = TOK_DELIM)
{
    std::vector<std::string> values;
    std::string s(strtok(line, delimiter));
    while (!s.empty())
    {
        values.push_back(s);
        s.clear();
        s.append(strtok(NULL, delimiter));
    }
    return values;
}
char **Analyser::split_str(char *line, const char *delimiter = TOK_DELIM)
{
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = (char **)calloc(bufsize, sizeof(char *));
    char *token = strtok(line, delimiter), **tokens_backup;

    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = (char **)realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                free(tokens_backup);
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, delimiter);
    }
    tokens[position] = NULL;
    return tokens;
}
bool Analyser::check(const char *word)
{
    std::vector<std::string>::iterator il = order.begin();
    while (il != order.end())
    {
        if (pile[*il].belongs(word))
        {
            return true;
        };
        il++;
    }
    return false;
};
Analyser::Analyser(/* args */)
{
}

Analyser::~Analyser()
{
}
string path = "/path/to/directory";
}; // namespace lexique
