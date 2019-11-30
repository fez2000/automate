#include "Automate.hpp"

namespace automate
{

Automate::Automate()
{
    init_sigma(DEFAULT_ALPHABET);
}
Automate::Automate(const char *alphabet)
{
    init_sigma(alphabet);
};
void Automate::print_states_finale()
{
    print_set_of_state(etatsFinaux);
};
void Automate::print_states_initial()
{
    print_set_of_state(etatsInitaux);
};
void Automate::print_set_of_state(const std::set<state> &s)
{
    std::set<state>::iterator il = s.begin();
    std::cout << "[";
    while (il != s.end())
    {
        std::cout << *il;
        if (++il != s.end())
            std::cout << ",";
    }
    std::cout << "]\n";
};
bool Automate::reach(state current, state a, std::set<state> &see)
{
    std::set<state>::iterator p;
    std::set<state> nexts = this->next_state_on(current);
    see.insert(current);

    if (nexts.find(a) != nexts.end())
    {
        return true;
    }

    p = nexts.begin();
    while (p != nexts.end())
    {
        if (see.find(*p) == nexts.end())
        {
            if (reach(*p, a, see))
            {
                return true;
            };
        }
        p++;
    }
    return false;
};
void Automate::print_alphabet()
{
    std::set<symbol>::iterator il = sigma.begin();
    while (il != sigma.end())
    {
        if (*il != EPSILONE)
            std::cout << *il;
        il++;
    }
    std::cout << std::endl;
};
void Automate::determiniser()
{
    std::vector<std::set<state> *> toExplore;
    std::map<symbol, std::vector<state> > dest;
    std::set<symbol>::iterator il;
    std::vector<std::set<state> >::iterator p;
    std::set<state>::iterator p2;

    std::map<symbol, std::vector<state> >::iterator il2;
    std::set<state> etats1, etatsFinaux1, etatsInitaux1;

    toExplore.push_back(&etatsInitaux);

    etatsInitaux1.insert(0);
    etats1.insert(0);
    il = sigma.begin();
    while (il != sigma.end())
    {
        std::vector<state> b;
        b.push_back(-1);
        dest.insert(std::make_pair(*il, b));
        il++;
    }

    size_t j = -1, e = 0;
    std::set<state>::iterator pp;

    while (e < toExplore.size())
    {

        j++;
        il = sigma.begin();
        std::set<state> *ep;
        while (il != sigma.end())
        {

            p2 = (*toExplore[e]).begin();
            ep = new std::set<state>;
            while (p2 != (*toExplore[e]).end())
            {

                //std::cout << p2->val() << (*toExplore[e]).get_length() << " hume " << *il << "\n";
                std::set<state> transiter = next_state_on((*p2), *il);

                if (transiter.size() > 0)
                {

                    pp = transiter.begin();
                    while (pp != transiter.end())
                    {

                        (*ep).insert(*pp);

                        pp++;
                    }
                }

                p2++;
            }

            size_t i = 0;
            while (i < toExplore.size())
            {
                if (are_equal_set(*toExplore[i], *ep))
                    break;
                i++;
            }

            if (i < toExplore.size())
            {

                dest[*il][j] = i;
            }
            else
            {

                if ((*ep).size() > 0)
                {
                    toExplore.push_back(ep);
                    il2 = dest.begin();
                    while (il2 != dest.end())
                    {

                        (*il2).second.push_back(-1);
                        il2++;
                    }

                    etats1.insert(toExplore.size() - 1);

                    if (is_finale(*ep))
                    {

                        etatsFinaux1.insert(toExplore.size() - 1);
                    }

                    dest[*il][j] = toExplore.size() - 1;
                };
            }

            il++;
        }

        e++;
    }

    il2 = dest.begin();
    this->etats.clear();
    this->etatsFinaux.clear();
    this->etatsInitaux.clear();
    graphe.clear();

    p2 = etats1.begin();
    while (p2 != etats1.end())
    {
        new_state(*p2);
        p2++;
    }

    p2 = etatsFinaux1.begin();
    while (p2 != etatsFinaux1.end())
    {
        make_finale(*p2);
        p2++;
    }

    p2 = etatsInitaux1.begin();
    while (p2 != etatsInitaux1.end())
    {
        make_initiale(*p2);
        p2++;
    }
    std::cout << "ajout des transition\n";

    std::cout << "graphe des transitions clean\n";
    while (il2 != dest.end())
    {

        size_t t = 0;
        while (t < (*il2).second.size())
        {

            if ((*il2).second[t] != -1)
                this->set_trans(t, (*il2).first, (*il2).second[t]);
            t++;
        }

        il2++;
    }
    std::cout << "end allgo\n";
};

bool Automate::is_trim_automaton()
{
    std::set<state>::iterator p = etats.begin();

    while (p != etats.end())
    {
        if (!useful(*p))
        {
            return false;
        };
        p++;
    }
    return true;
};
bool Automate::accessible(state a)
{
    std::set<state> see, nexts;
    std::set<state>::iterator p;
    if (etatsInitaux.find(a) != etatsFinaux.end())
    {
        return true;
    }

    p = etats.begin();
    while (p != etats.end())
    {
        if (reach(*p, a, see))
            return true;

        p++;
    }
    return false;
};
bool Automate::coaccessible(state s)
{
    std::set<state> see, nexts;
    std::set<state>::iterator p;
    if (etatsFinaux.find(s) != etatsFinaux.end())
    {
        return true;
    }

    p = etats.begin();
    while (p != etats.end())
    {
        if (reachEnd(*p, see))
            return true;

        p++;
    }
    return false;
};
bool Automate::useful(state s)
{
    return accessible(s) && coaccessible(s);
};
bool Automate::reachEnd(state current, std::set<state> &see)
{
    std::set<state>::iterator p;
    std::set<state> nexts = this->next_state_on(current);
    see.insert(current);

    if (etatsFinaux.find(current) != etatsFinaux.end())
    {
        return true;
    }

    p = nexts.begin();
    while (p != nexts.end())
    {
        if (see.find(*p) == see.end())
        {
            if (reachEnd(*p, see))
            {
                return true;
            };
        }
        p++;
    }
    return false;
};
void Automate::init_sigma(const symbol *alphabet)
{
    sigma.clear();
    size_t n = strlen(alphabet), j = 0;
    while (j < n)
    {
        sigma.insert(alphabet[j]);
        j++;
    }
    //sigma.insert(EPSILONE);
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
    std::vector<std::set<symbol> *> b;
    graphe.push_back(b);

    while (j < graphe.size())
    {
        k = graphe[j].size();
        while (k <= graphe.size())
        {
            graphe[j].push_back(new std::set<symbol>);
            k++;
        }
        j++;
    }
    return graphe.size() - 1;
}
state Automate::new_state()
{
    state e = _new_state();
    etats.insert(e);
    return e;
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
    std::cout << graphe[from][to]->size();
    graphe[from][to]->insert(a);
    std::cout << graphe[from][to]->size();
};
bool Automate::is_full()
{

    std::set<symbol>::iterator il = sigma.begin();
    std::set<state>::iterator p;
    std::set<state> transiter;
    while (il != sigma.end())
    {

        p = etats.begin();
        while (p != etats.end())
        {
            transiter = this->next_state_on(*p, *il);
            if (transiter.size() == 0 && *il != EPSILONE)
            {
                return false;
            }
            p++;
        }
        il++;
    }

    return true;
};
void Automate::make_full()
{

    std::set<symbol>::iterator il = sigma.begin();
    std::set<state>::iterator p;
    std::set<state> transiter;
    bool hasPuis = false;
    state puis;
    while (il != sigma.end())
    {

        p = etats.begin();
        while (p != etats.end())
        {
            transiter = next_state_on(*p, *il);
            if (transiter.size() == 0 && *il != EPSILONE)
            {
                if (hasPuis)
                {
                    this->set_trans(puis, *il, puis);
                    this->set_trans(*p, *il, puis);
                }
                else
                {
                    puis = new_state();
                    this->set_trans(puis, *il, puis);
                    this->set_trans(*p, *il, puis);
                }
            }
            p++;
        }
        il++;
    }
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
            graphe[s][j]->erase(il);

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
        graphe[s][j]->erase(a);
        j++;
    }
};
void Automate::del_trans_on_to(state s, symbol a, state d)
{
    graphe[s][d]->erase(a);
};
void Automate::del_trans_all_to(state destination)
{
    size_t j = 0;
    while (j < etats.size())
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

    size_t j = 0;
    del_trans(s);
    while (j < graphe[s].size())
    {
        graphe[s][j]->clear();
    }

    j = 0;
    while (j < etats.size())
    {
        if (j != s)
        {
            del_trans_all_to(s);

            //remove_col_on_line(s, j);
        }
    }
    //remove_line(s);
    etats.erase(s);
    etatsFinaux.erase(s);
    etatsInitaux.erase(s);
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
void Automate::append_state(state s)
{
    this->etats.insert(s);
};
void Automate::make_finale(state s)
{
    this->etatsFinaux.insert(s);
};
void Automate::make_initiale(state s)
{
    this->etatsInitaux.insert(s);
};
void Automate::remove_state(state s)
{
    this->etats.erase(s);
    this->remove_state_finale(s);
    this->remove_state_initiale(s);
};
void Automate::remove_state_finale(state s)
{
    this->etatsFinaux.erase(s);
};
void Automate::remove_state_initiale(state s)
{
    this->etatsInitaux.erase(s);
};
bool Automate::is_finale(state s)
{
    return this->etatsFinaux.find(s) != this->etatsFinaux.end();
};
bool Automate::is_finale(const std::set<state> &s)
{
    std::set<state>::iterator p = s.begin();
    bool isFinal = false;
    while (p != s.end())
    {
        if (is_finale(*p))
        {
            return true;
        }

        p++;
    }

    return false;
};
void Automate::print()
{
    std::set<state>::iterator p, p2;
    std::set<symbol>::iterator p3;
    size_t i = 0, j = 0;
    p = etats.begin();

    while (p != etats.end())
    {
        p2 = etats.begin();
        while (p2 != etats.end())
        {

            p3 = graphe[*p][*p2]->begin();
            while (p3 != graphe[*p][*p2]->end())
            {
                std::cout << "( " << *p << ", " << *p3 << ", " << *p2 << ")\n";
                p3++;
            }
            p2++;
        }
        p++;
    }
};
bool Automate::is_initiale(state s)
{
    return this->etatsInitaux.find(s) != this->etatsInitaux.end();
};
bool Automate::calculate_word_at(const symbol *word, state start)
{
    size_t n = strlen(word);
    std::set<state>::iterator p;
    std::set<state> transiter = this->next_state_on(start, word[0]);

    std::ostringstream oss;
    p = transiter.begin();
    bool isBelong = false;

    if (transiter.size() == 0)
    {

        oss << "transition non definie on state " << start << " with label " << word[0];

        throw my_exception(oss.str().c_str());
        return false;
    }

    if (n == 1)
    {

        while (p != transiter.end())
        {
            if (this->etatsFinaux.find(*p) != etatsFinaux.end())
            {
                return true;
            }
            p++;
        }
        return false;
    }
    else
    {
        ;
        while (p != transiter.end())
        {

            isBelong = isBelong || calculate_word_at(word + 1, *p);
            p++;
        }
    }

    return isBelong;
};
bool Automate::check_symbol(const symbol word)
{

    return sigma.find(word) != sigma.end();
};
bool Automate::check_symbols(const symbol *word)
{
    size_t n = strlen(word), j = 0;
    if (n == 0)
    {
        if (sigma.find('\0') != sigma.end())
        {
            return true;
        }
        return false;
    }
    while (j++ < n)
    {
        if (sigma.find(word[j]) == sigma.end())
            return false;
    }
    return true;
};
bool Automate::belongs(const symbol *word)
{
    size_t n = strlen(word);
    std::set<state>::iterator p;

    bool isBelong = false;
    p = this->etatsInitaux.begin();
    if (n == 0)
    {
        while (p != this->etatsInitaux.end())
        {
            isBelong = isBelong || (this->etatsFinaux.find(*p) != etatsFinaux.end());
            p++;
        }
    }
    else
    {

        while (p != this->etatsInitaux.end())
        {
            isBelong = isBelong || this->calculate_word_at(word, *p);

            p++;
        }
    }
    return isBelong;
};
std::set<state>
Automate::next_state_on(state s)
{
    size_t j = 0;
    std::set<state> transiter;
    while (j <= etats.size())
    {
        if (graphe[s][j]->size() > 0)
        {

            transiter.insert(j);
        }
        j++;
    };

    return transiter;
};
std::set<state>
Automate::next_state_on(std::set<state> s, symbol a)
{
    std::set<state>::iterator p = s.begin();
    std::set<state> trasitions;
    while (p != s.end())
    {
        std::set<state> tmp = next_state_on(*p, a);
        trasitions.swap(tmp);
        p++;
    }
    return trasitions;
};
std::set<state> Automate::next_state_on(state s, symbol a)
{
    size_t j = 0;
    std::set<state> transiter;
    std::set<state>::iterator il;
    il = etats.begin();
    while (il != etats.end())
    {
        if (graphe[s][*il]->find(a) != graphe[s][*il]->end())
        {

            transiter.insert(*il);
        }
        il++;
    };

    return transiter;
};
// Modification
//void initial(state s);
void copy_state(state from, state to);
void change_trans(state s, symbol a, state new_aim);
} // namespace  automate
