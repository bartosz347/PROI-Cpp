#include "Money.h"

using namespace std;


// legacy
Money::Money(string name, double rateInEuro, long int value) // todo should not use double, all should be int (nice rates could be used)
{
    this->name = name;
    this->rateInEuro = lround(rateInEuro*100); // 4.3099 -> 431
    this->value = Number(value); // realValue := value/100
}

Money::Money(string name, int rateInEuro, long int value)
{
    this->name = name;
    this->rateInEuro = rateInEuro; // 431
    this->value = Number(value); // realValue := value/100
}

Number Money::getInEuro() const
{
    //double r = round(this->value / (double)this->rateInEuro); // TODO rounding ?
    return this->value / this->rateInEuro; // TODO rounding ?
}

void Money::add(Money curr)
{
    if(this->name.compare(curr.name) == 0)
        this->value +=curr.value;
     else
        this->value += curr.getInEuro()*this->rateInEuro;
}

string Money::getFormattedValue()
{
    return string(this->name + " " + to_string(this->getMainValue()) + "." + to_string(this->getCentsValue()));
}







