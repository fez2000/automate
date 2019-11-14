#include "Automate.hpp"

namespace automate
{
Automate::Automate()
{
    init_sigma(DEFAULT_ALPHABET);
}

void Automate::init_sigma(const symbol *alphabet)
{
    sigma.clear();
    sigma.insert(alphabet, alphabet + sizeof(alphabet) - 1);
    sigma.insert(EPSILONE);
};
Automate::~Automate()
{
    size_t j = 0, i = 0;
    while (i < graphe.size())
    {
        j = 0;
        while (j < graphe[i].size())
        {
            delete graphe[i][j];
            j++;
        }
        i++;
    }
}
state Automate::_new_state()
{
    size_t k = graphe.size(), j = 0;
    std::vector<Liste<symbol> *> b;
    graphe.push_back(b);

    while (j < graphe.size())
    {
        k = graphe[j].size();
        while (k <= graphe.size())
        {
            graphe[j].push_back(new Liste<symbol>);
            k++;
        }
        j++;
    }
    return graphe.size() - 1;
}
state Automate::new_state()
{

    etats.add(new Cellule<state>(_new_state()));
    return etats.get_sentries()->prev()->val();
};
void Automate::new_state(state i)
{

    while (graphe.size() < i)
    {
        _new_state();
    }
    new_state();
};
void Automate::set_trans(state from, symbol a, state to)
{
    graphe[from][to]->add(new Cellule<symbol>(a));
};
bool Automate::is_full()
{
    size_t nb = 0, i = 0, k = 0;
    while (i < graphe.size())
    {
        k = 0;
        nb = 0;
        while (k < graphe[i].size())
        {
            nb += graphe[i][k]->get_length();
            k++;
        }
        if (nb != (sigma.size() - 1))
        {
            return false;
        }
        i++;
    }
    return true;
};
void Automate::del_trans(state s)
{
    size_t j = 0;
    std::set<symbol>::iterator il;
    while (j < graphe[s].size())
    {
        il = sigma.begin();
        while (il != sigma.end())
        {
            graphe[s][j]->removeByValue(*il);

            il++;
        }
        j++;
    }
};
void Automate::del_trans_on(state s, symbol a)
{
    size_t j = 0;
    while (j < graphe[s].size())
    {
        graphe[s][j]->removeByValue(a);
        j++;
    }
};
void Automate::del_trans_on_to(state s, symbol a, state d)
{
    graphe[s][d]->removeByValue(a);
};
void Automate::del_trans_all_to(state destination)
{
    size_t j = 0;
    while (j < etats.get_length())
    {
        if (j != destination)
        {
            graphe[j][destination]->clear();
        }
        j++;
    }
};
//state duplicate_state(state s);
void Automate::del_state(state s)
{

    size_t i = graphe.size(), j = 0, k = 0;
    del_trans(s);
    while (j < graphe[s].size())
    {
        graphe[s][j]->clear();
    }

    j = 0;
    while (j < etats.get_length())
    {
        if (j != s)
        {
            del_trans_all_to(s);

            //remove_col_on_line(s, j);
        }
    }
    //remove_line(s);
    etats.removeByValue(s);
    etatsFinaux.removeByValue(s);
    etatsInitaux.removeByValue(s);
};
void Automate::remove_line(size_t i)
{

    while ((i + 1) < graphe.size())
    {
        graphe[i] = graphe[i + 1];
        i++;
    }
    graphe.pop_back();
};
void Automate::remove_col_on_line(size_t j, size_t i)
{
    while ((j + 1) < graphe[i].size())
    {
        graphe[i][j] = graphe[i][j + 1];
        j++;
    }
    graphe[i].pop_back();
};
// Modification
//void initial(state s);
void copy_state(state from, state to);
void change_trans(state s, symbol a, state new_aim);
} // namespace  automate
