#include "Currency.h"

using namespace std;

Currency::Currency(string name, double rateInEuro, int value) // todo should not use double, all should be int (nice rates could be used)
{
    this->name = name;
    this->rateInEuro = lround(rateInEuro*100); // 4.3099 -> 431
    this->value = value; // realValue := value/100
}

Currency::Currency(string name, int rateInEuro, int value)
{
    this->name = name;
    this->rateInEuro = rateInEuro; // 431
    this->value = value; // realValue := value/100
}

long int Currency::getInEuro() const
{
    double r = round(this->value / (double)this->rateInEuro); // TODO rounding ?
    return r;
}

void Currency::add(Currency curr)
{
    if(this->name.compare(curr.name) == 0)
        this->value +=curr.value;
     else
        this->value += curr.getInEuro()*this->rateInEuro;
}

string Currency::getFormattedValue() const
{
    return string(this->name + " " + to_string(this->getMainValue()) + "." + to_string(this->getCentsValue()));
}








