#include "TestClass.hpp"

namespace test
{
Test::Test(/* args */)
{
}

Test::~Test()
{
}
void Test::addUnit(UnitTest u)
{
    this->units.add(new Cellule<UnitTest>(u));
};
void Test::make()
{
    Cellule<UnitTest> *p;
    p = units.get_head();
    while (p != units.get_sentries())
    {

        p->val().makeTest(&allValue);

        p = p->next();
    }
};
} // namespace test