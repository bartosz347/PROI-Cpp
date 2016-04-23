#include "Money.h"

using namespace std;

template<currencyTag T>
std::string Money<T>::Money::currencyTagNames[CURRENCIES_NO] = {CURRENCIES_STRING};

template<currencyTag T>
int Money<T>::Money::currencyRates[CURRENCIES_NO] = {CURRENCIES_RATES};



template<currencyTag T>
Money<T>::Money(long int value):
    rateInEuro(currencyRates[static_cast<int>(T)]), // like 431
    value(Number{value})    // realValue := value/100
{ }

template<currencyTag T>
Money<T>::Money(Number value)
{
    this->rateInEuro = currencyRates[static_cast<int>(T)];
    this->value = value; // realValue := value/100
}


template<currencyTag T>
Number Money<T>::getInEuro() const
{
    return this->value / this->rateInEuro; // TODO rounding ?
}


template<currencyTag T>
string Money<T>::toString()
{
    return string(this->getStringName() + " " + to_string(this->getMainValue()) + "." + to_string(this->getCentsValue()));
}









