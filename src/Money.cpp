#include "Money.h"

using namespace std;

template<currencyTag T>
std::string Money<T>::Money::currencyTagNames[CURRENCIES_NO] = {CURRENCIES_STRING};

template<currencyTag T>
int Money<T>::Money::currencyRates[CURRENCIES_NO] = {CURRENCIES_RATES};



template<currencyTag T>
Money<T>::Money(long int value):
    rateInEuro(currencyRates[static_cast<int>(T)]), // like 420
    value(Number{value})    // realValue := value/100
{}

template<currencyTag T>
Money<T>::Money(Number value) :
    rateInEuro(currencyRates[static_cast<int>(T)]),
    value{value} // realValue := value/100
{}

template<currencyTag T>
Money<T>::Money(std::string numberString) :
    rateInEuro(currencyRates[static_cast<int>(T)]),
    value{Number{numberString}}
{}


template<currencyTag T>
Number Money<T>::getInEuro() const
{
    return this->value / this->rateInEuro;
}


template<currencyTag T>
string Money<T>::toString() const
{
    return string(this->getStringName() + CURRENCY_SEPARATOR
                  + to_string(this->getMainValue()) + DECIMAL_SEPARATOR + to_string(this->getCentsValue()));
}


template class Money<currencyTag::PLN>; // TODO fixme ASK
template class Money<currencyTag::GBP>;







