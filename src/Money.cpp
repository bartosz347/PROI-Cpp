#include "Money.h"

using namespace std;

template<currencyTag T>
std::string Money<T>::Money::currencyTagNames[CURRENCIES_NO] = {CURRENCIES_STRING};



template<currencyTag T>
Money<T>::Money(int rateInEuro, long int value)
{
    this->rateInEuro = rateInEuro; // 431
    this->value = Number(value); // realValue := value/100
}

template<currencyTag T>
Money<T>::Money(int rateInEuro, Number value)
{
    this->rateInEuro = rateInEuro; // 4.3099 -> 431
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








