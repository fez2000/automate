#include "Erreur.hpp"
const char *my_exception::what() const _GLIBCXX_USE_NOEXCEPT
{
    return ad_texte;
};
my_exception::my_exception(char *texte) { ad_texte = texte; };
my_exception::my_exception(const char *texte)
{
    ad_texte = strdup(texte);
};
my_exception::~my_exception() _GLIBCXX_USE_NOEXCEPT
{
    free(ad_texte);
};