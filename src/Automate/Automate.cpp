#include "Automate.hpp"

namespace automate
{
std::set<state> Automate::states()
{
    return etats;
};
std::set<state> Automate::states_initial()
{
    return etatsInitaux;
};
std::set<state> Automate::states_finale()
{
    return etatsFinaux;
};
Automate::Automate()
{
    init_sigma(DEFAULT_ALPHABET);
}
Automate::Automate(const char *alphabet)
{
    init_sigma(alphabet);
};
Automate::Automate(std::set<symbol> b)
{
    set_insert(sigma, b);
};
std::string Automate::print_states_finale_str()
{
    return print_set_of_state_str(etatsFinaux);
};
std::string Automate::print_states_str()
{
    return print_set_of_state_str(etats);
};
std::string Automate::print_states_initial_str()
{
    return print_set_of_state_str(etatsInitaux);
};
void Automate::print_states_finale()
{
    print_set_of_state(etatsFinaux);
};
void Automate::print_states_initial()
{
    print_set_of_state(etatsInitaux);
};
std::string Automate::print_set_of_state_str(const std::set<state> &s)
{
    std::stringstream out;
    std::set<state>::iterator il = s.begin();
    out << "[";
    while (il != s.end())
    {
        out << *il;
        if (++il != s.end())
            out << ",";
    }
    out << "]\n";
    return out.str();
};
void Automate::print_set_of_state(const std::set<state> &s)
{
    std::cout << print_set_of_state_str(s);
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
std::string Automate::print_alphabet_str()
{
    std::set<symbol>::iterator il = sigma.begin();
    std::stringstream out;
    while (il != sigma.end())
    {
        if (*il != EPSILONE)
            out << *il;
        il++;
    }
    out << std::endl;
    return out.str();
};
void Automate::print_alphabet()
{

    std::cout << print_alphabet_str();
};
void Automate::remove_epsilon_transition(state e)
{
    std::set<state>::iterator il, il2, il3;

    std::set<state> nexts = next_state_on(e, EPSILONE), nexts2;

    std::set<symbol>::iterator p;
    il = nexts.begin();

    while (il != nexts.end())
    {
        if (is_finale(nexts))
            make_finale(e);
        if (is_initiale(nexts))
            make_initiale(e);

        nexts2 = next_state_on(*il);
        il2 = nexts2.begin();

        graphe[e][*il]->erase(EPSILONE);
        while (il2 != nexts2.end())
        {
            std::set<symbol>::iterator p = graphe[*il][*il2]->begin();
            while (p != graphe[*il][*il2]->end())
            {
                set_trans(*il, *p, *il2);
                p++;
            }
            il2++;
        }
        il++;
    }
}
void Automate::complementary()
{
    make_full();
    std::set<state>::iterator il;
    std::set<state> notFinale;
    il = etats.begin();
    while (il != etats.end())
    {
        if (etatsFinaux.find(*il) == etatsFinaux.end())
        {
            notFinale.insert(*il);
        }
        il++;
    }
    etatsFinaux.clear();
    set_insert(etatsFinaux, notFinale);
};
void Automate::miroir()
{
    std::set<state>::iterator il, il2;

    il = etats.begin();
    while (il != etats.end())
    {
        il2 = etats.begin();
        while (il2 != etats.end())
        {
            std::set<symbol> current;
            if (*il2 < *il)
            {
                set_insert(current, *graphe[*il][*il2]);
                graphe[*il][*il2]->clear();
                set_insert(*graphe[*il][*il2], *graphe[*il2][*il]);
                graphe[*il2][*il]->clear();
                set_insert(*graphe[*il2][*il], current);
            }

            il2++;
        }

        il++;
    }

    std::set<state> c;
    set_insert(c, etatsFinaux);
    etatsFinaux.clear();
    set_insert(etatsFinaux, etatsInitaux);
    etatsInitaux.clear();
    set_insert(etatsInitaux, c);
};
void Automate::standardisation()
{
    if (etatsInitaux.size() < 2)
        return;
    std::set<state>::iterator il, il2, il3;
    state e = new_state();
    if (is_finale(etatsInitaux))
        make_finale(e);
    while (il != etatsInitaux.end())
    {
        il2 = etats.begin();
        while (il2 != etats.end())
        {
            set_insert(*graphe[e][*il2], *graphe[*il][*il2]);
            il2++;
        }
    }
    etatsInitaux.clear();
    etatsInitaux.insert(e);

    std::set<state> nexts = next_state_on(e, EPSILONE), nexts2;
};
void Automate::remove_epsilon_transition()
{
    std::set<state>::iterator il;

    do
    {
        il = etats.begin();
        while (il != etats.end())
        {

            remove_epsilon_transition(*il);

            il++;
        }

    } while (has_epsilon_transition());
};
bool Automate::has_epsilon_transition(state e)
{
    std::set<state>::iterator il = etats.begin();
    while (il != etats.end())
    {
        if (graphe[e][*il]->find(EPSILONE) != graphe[e][*il]->end())
            return true;
        il++;
    }
    return false;
};
bool Automate::has_epsilon_transition()
{
    std::set<state>::iterator il;
    il = etats.begin();
    while (il != etats.end())
    {
        if (has_epsilon_transition(*il))
        {
            return true;
        }
        il++;
    }
    return false;
};
bool has_equal_sigma(Automate &a1, Automate &a2)
{
    return are_equal_set(a1.sigma, a2.sigma);
};
Automate *intersection_closing(Automate a1, Automate a2)
{
    Automate *b = new Automate(a1.sigma);
    std::map<state, std::map<state, int> > t;
    std::set<state>::iterator il = a1.etats.begin();
    while (il != a1.etats.end())
    {
        std::set<state>::iterator p = a2.etats.begin();
        while (p != a2.etats.end())
        {
            t[*il][*p] = b->new_state();
            if (a1.is_finale(*il) && a2.is_finale(*p))
            {
                b->make_finale(t[*il][*p]);
            }

            p++;
        }
        il++;
    }
    b->make_initiale(t[*a1.etatsInitaux.begin()][*a2.etatsInitaux.begin()]);
    il = a1.etats.begin();
    while (il != a1.etats.end())
    {
        std::set<state>::iterator p = a2.etats.begin();

        while (p != a2.etats.end())
        {

            std::set<symbol>::iterator sp = b->sigma.begin();
            while (sp != b->sigma.end())
            {
                std::set<state> next1 = a1.next_state_on(*il, *sp);
                std::set<state> next2 = a2.next_state_on(*p, *sp);
                b->set_trans(t[*il][*p], *sp, t[*next1.begin()][*next2.begin()]);
                sp++;
            }

            p++;
        }
        il++;
    }
    return b;
};
Automate *opt_plus(Automate a1, Automate a2){

};
Automate *opt_concat(Automate a1, Automate a2){

};
Automate *opt_etoille(Automate a1, Automate a2){

};
Automate *concatenation_closing(Automate a1, Automate a2)
{
    Automate *b = new Automate(a1.sigma);
    std::map<state, state> t1, t2;
    std::set<state>::iterator il1 = a1.etats.begin();
    std::set<state>::iterator il2 = a2.etats.begin();
    set_insert(b->sigma, a2.sigma);
    while (il1 != a1.etats.end())
    {
        t1[*il1] = b->new_state();
        if (a1.is_initiale(*il1))
            b->make_initiale(t1[*il1]);
        il1++;
    }
    while (il2 != a2.etats.end())
    {
        t2[*il2] = b->new_state();
        if (a1.is_finale(*il1))
            b->make_finale(t1[*il1]);
        if (a2.is_initiale(*il2))
        {
            il1 = a1.etatsFinaux.begin();
            while (il1 != a1.etatsFinaux.end())
            {
                b->set_trans(t1[*il1], '\0', t2[*il2]);
                il1++;
            }
        }
        il2++;
    }
    il1 = a1.etats.begin(), il2 = a1.etats.begin();
    while (il1 != a1.etats.end())
    {
        while (il2 != a1.etats.end())
        {
            set_insert(*b->graphe[t1[*il1]][t1[*il2]], *a1.graphe[*il1][*il2]);
            il2++;
        }
        il1++;
    }
    il1 = a2.etats.begin(), il2 = a2.etats.begin();
    while (il1 != a2.etats.end())
    {
        while (il2 != a2.etats.end())
        {
            set_insert(*b->graphe[t2[*il1]][t2[*il2]], *a2.graphe[*il1][*il2]);
            il2++;
        }
        il1++;
    }
    b->remove_epsilon_transition();
    return b;
};
Automate *unionof_closing(Automate a1, Automate a2)
{
    Automate *b = new Automate(a1.sigma);
    std::map<state, std::map<state, int> > t;
    std::set<state>::iterator il = a1.etats.begin();
    std::set<state>::iterator p;
    set_insert(b->sigma, a2.sigma);

    while (il != a1.etats.end())
    {
        p = a2.etats.begin();
        while (p != a2.etats.end())
        {
            t[*il][*p] = b->new_state();
            if (a1.is_finale(*il) || a2.is_finale(*p))
            {
                b->make_finale(t[*il][*p]);
            }

            p++;
        }
        il++;
    }
    b->make_initiale(t[*a1.etatsInitaux.begin()][*a2.etatsInitaux.begin()]);
    il = a1.etats.begin();
    while (il != a1.etats.end())
    {
        std::set<state>::iterator p = a2.etats.begin();

        while (p != a2.etats.end())
        {

            std::set<symbol>::iterator sp = b->sigma.begin();
            while (sp != b->sigma.end())
            {
                std::set<state> next1 = a1.next_state_on(*il, *sp);
                std::set<state> next2 = a2.next_state_on(*p, *sp);
                b->set_trans(t[*il][*p], *sp, t[*next1.begin()][*next2.begin()]);
                sp++;
            }

            p++;
        }
        il++;
    }
    return b;
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
    std::set<state> see;
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
    std::set<state> see;
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
std::set<state> Automate::epsilon_closing(std::set<state> s)
{
    std::set<state> all;
    std::set<state>::iterator il = s.begin();
    while (il != s.end())
    {
        std::set<state> tmp = epsilon_closing(*il);
        set_insert(all, tmp);
        il++;
    }
    return all;
};
std::set<state> Automate::transit(std::set<state> s, symbol a)
{
    std::set<state> all;
    std::set<state>::iterator il = s.begin();
    while (il != s.end())
    {
        std::set<state> tmp = transit(*il, a);
        set_insert(all, tmp);
        il++;
    }
    return all;
};

std::set<state> Automate::transit(state e, symbol a)
{
    std::set<state> see;
    return transit(e, a, see);
};
std::set<state> Automate::transit(state e, symbol a, std::set<state> &see)
{
    std::set<state> nexts = next_state_on(e, a);
    std::set<state>::iterator il = nexts.begin();
    while (il != nexts.end())
    {
        if (see.find(*il) != see.end())
        {
            see.insert(*il);
            epsilon_closing(*il, see);
        }
        il++;
    }
    return see;
};
std::set<state> Automate::epsilon_closing(state e, std::set<state> &see)
{
    std::set<state> nexts = next_state_on(e, EPSILONE);
    std::set<state>::iterator il = nexts.begin();
    while (il != nexts.end())
    {
        if (see.find(*il) != see.end())
        {
            see.insert(*il);
            epsilon_closing(*il, see);
        }
        il++;
    }
    return see;
};
std::set<state> Automate::epsilon_closing(state e)
{
    std::set<state> see;
    return epsilon_closing(e, see);
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

    while (graphe.size() < (unsigned int)i)
    {
        _new_state();
    }
    if (graphe.size() == i)
    {
        new_state();
    }
    else
    {
        etats.insert(i);
    }
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

    std::set<symbol>::iterator il;
    std::set<state>::iterator p;
    std::set<state> transiter;
    bool hasPuis = false;
    state puis;
    p = etats.begin();
    size_t j = 0;
    while (p != etats.end() && j < etats.size())
    {
        if (*p == puis && hasPuis)
        {

            p++;
            continue;
        }

        il = sigma.begin();
        while (il != sigma.end())
        {

            transiter = next_state_on(*p, *il);
            if (transiter.size() == 0 && *il != EPSILONE)
            {
                if (hasPuis)
                {

                    this->set_trans(*p, *il, puis);
                }
                else
                {
                    hasPuis = true;
                    puis = new_state();
                    set_insert(*graphe[puis][puis], sigma);

                    this->set_trans(*p, *il, puis);
                }
            }
            il++;
        }
        j++;
        p++;
    }
};
void Automate::del_trans(state s)
{
    size_t j = 0;
    std::set<symbol>::iterator il;
    while (j < graphe[s].size())
    {
        graphe[s][j]->clear();
        j++;
    }
};
void Automate::del_trans_on(state s, symbol a)
{
    std::set<state>::iterator il = etats.begin();
    while (il != etats.end())
    {
        graphe[s][*il]->erase(a);
        il++;
    }
};
void Automate::del_trans_on_to(state s, symbol a, state d)
{
    graphe[s][d]->erase(a);
};
void Automate::del_trans_all_to(state destination)
{
    std::set<state>::iterator il = etats.begin();
    while (il != etats.end())
    {
        if (*il != destination)
        {
            graphe[*il][destination]->clear();
        }
        il++;
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
        if (j != (unsigned int)s)
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
bool Automate::is_state(state s)
{
    return this->etats.find(s) != this->etats.end();
};
bool Automate::is_initiale(const std::set<state> &s)
{
    std::set<state>::iterator p = s.begin();

    while (p != s.end())
    {
        if (is_initiale(*p))
        {
            return true;
        }

        p++;
    }

    return false;
};
bool Automate::is_finale(const std::set<state> &s)
{
    std::set<state>::iterator p = s.begin();

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
std::string Automate::print_str()
{
    std::set<state>::iterator p, p2;
    std::set<symbol>::iterator p3;
    std::stringstream out;
    p = etats.begin();

    while (p != etats.end())
    {
        p2 = etats.begin();
        while (p2 != etats.end())
        {

            p3 = graphe[*p][*p2]->begin();
            while (p3 != graphe[*p][*p2]->end())
            {
                out << "( " << *p << ", " << *p3 << ", " << *p2 << ")\n";
                p3++;
            }
            p2++;
        }
        p++;
    }
    return out.str();
};
void Automate::print()
{
    std::cout << print_str();
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

        throw new my_exception(oss.str().c_str());
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

        set_insert(trasitions, tmp);
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
void Automate::duplicate_state(state from, state to)
{
    copy_state(from, to);
};
state Automate::duplicate_state(state e)
{
    state a = new_state();
    copy_state(e, a);
    return a;
};
void Automate::copy_state(state from, state to)
{
    del_trans_all_to(to);
    del_trans(to);
    std::set<state>::iterator il = etats.begin();
    while (il != etats.end())
    {
        graphe[*il][to] = new std::set<symbol>(*graphe[*il][from]);
        graphe[to][*il] = new std::set<symbol>(*graphe[from][*il]);
        il++;
    };
};
void change_trans(state s, symbol a, state new_aim);
bool Automate::is_deterministe()
{
    std::set<state>::iterator il = etats.begin();
    while (il != etats.end())
    {
        std::set<state>::iterator to = etats.begin();
        std::map<symbol, int> num;
        while (to != etats.end())
        {
            std::set<symbol>::iterator p = graphe[*il][*to]->begin();
            while (p != graphe[*il][*to]->end())
            {
                if (!num[*p])
                {
                    num[*p] = 1;
                }
                else
                {
                    num[*p]++;
                }

                p++;
            }

            to++;
        };
        std::map<symbol, int>::iterator r = num.begin();
        while (r != num.end())
        {
            if (r->second > 1)
                return false;
            r++;
        }

        il++;
    };
    return true;
};
std::set<symbol> Automate::get_sigma()
{
    return sigma;
};

void Automate::etoile_closing()
{
    this->set_trans(*etatsFinaux.begin(), '\0', *etatsInitaux.begin());
    make_finale(*etatsInitaux.begin());
};
Automate *etoile_closing(Automate a1)
{
    Automate *a2 = new Automate(a1);
    a2->etoile_closing();
    return a2;
};
} // namespace  automate
