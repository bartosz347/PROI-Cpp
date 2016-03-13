#include "Currency.h"

Currency::Currency(std::string name, int rateInEuro, int value = 0)
{
    this.name = name;
    this.rateInEuro = rateInEuro;
    this.value = value;
}

Currency::multiply(int m)
{
    this.value = m*value;
}

Currency::addSame(Currency curr)
{
    this.value += curr.value;
}

Currency::addFromEuro()

Currency::add(Currency curr)
{
    if(this.name == curr.name) {
        addSame(curr);
    }
    else {
        addSame

    }

}

Currency::
