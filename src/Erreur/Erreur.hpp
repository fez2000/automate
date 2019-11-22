#ifndef ERREUR_H_INCLUCE
#define ERREUR_H_INCLUDE
#include <stdlib.h>
#include <stdexcept>
#include <string.h>
class my_exception : public std::exception
{
public:
    my_exception(char *texte);
    my_exception(const char *texte);
    ~my_exception() _GLIBCXX_USE_NOEXCEPT;
    const char *what() const _GLIBCXX_USE_NOEXCEPT;

private:
    char *ad_texte;
};

#endif