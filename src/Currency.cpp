#include "Currency.h"

using namespace std;

Currency::Currency(std::string name, double rateInEuro, int value)
{
    this->name = name;
    this->rateInEuro = lround(rateInEuro*100); // 4.3099 -> 431
    this->value = value; // realValue := value/100
}

void Currency::multiply(int m)
{
    this->value =getMultiplied(m);
}

long int Currency::getMultiplied(int m)
{
    return m*value;
}

int Currency::getInEuro()
{
    return this->value / this->rateInEuro;
}

long int Currency::getSum(Currency curr)
{
    if(this->name.compare(curr.name) == 0)
        return curr.value + this->value;
     else
        return curr.getInEuro()*this->rateInEuro + this->value;
}

void Currency::add(Currency curr)
{
    this->value = getSum(curr);
}

void Currency::assign(Currency curr)
{
    this->name = curr.name;
    this->value = curr.value;
    this->rateInEuro = curr.rateInEuro;
}

string Currency::getFormattedValue()
{
    return string(to_string(this->getMainValue()) + "." + to_string(this->getCentsValue()));
}

