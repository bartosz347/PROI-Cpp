#include "Money.h"

using namespace std;

template<CurrencyTag T>
const struct MoneyConfig Money<T>::conf;

template<CurrencyTag T>
Money<T>::Money(Number value) :
    value{value} // realValue := value/100
{}



template<CurrencyTag T>
Number Money<T>::getInEuro() const
{
    return this->value / this->getEuroRate();
}


template<CurrencyTag T>
string Money<T>::toString() const
{
    return string(this->getStringName() + Money::conf.CURRENCY_SEPARATOR
                  + to_string(this->getMainValue()) + Money::conf.DECIMAL_SEPARATOR + to_string(this->getCentsValue()));
}


template class Money<CurrencyTag::PLN>; // TODO fixme ASK
template class Money<CurrencyTag::GBP>;







