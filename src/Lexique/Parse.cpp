#include "Parse.hpp"
#include <string>
#include <iostream>

namespace lexique
{
using namespace std;
std::vector<std::string> Analyser::split(char *line, const char *delimiter = TOK_DELIM)
{
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = (char **)calloc(bufsize, sizeof(char *));
    std::vector<std::string> values;
    char *token = strtok(line, delimiter), **tokens_backup;

    std::string s(token);
    while (token != NULL)
    {
        tokens[position] = token;

        values.push_back(s);
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
        s.clear();
        s.append(strtok(NULL, delimiter));
    }
    return values;
}
std::vector<std::string> Analyser::split(char *line, const char *delimiter = TOK_DELIM)
{
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = (char **)calloc(bufsize, sizeof(char *));
    std::vector<std::string> values;
    char *token = strtok(line, delimiter), **tokens_backup;

    std::string s(token);
    while (token != NULL)
    {
        tokens[position] = token;

        values.push_back(s);
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
        s.clear();
        s.append(token);
    }
    tokens[position] = NULL;
}
Analyser::Analyser(/* args */)
{
}

Analyser::~Analyser()
{
}
string path = "/path/to/directory";
}; // namespace lexique
