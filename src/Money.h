#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>
#include <math.h>

#include "Number.h"

enum class currencyTag
{
    PLN, GBP, USD
};


template <currencyTag T> class Money
{
    template<currencyTag K> // Lets us access private properties (like value) from all variations of Money http://stackoverflow.com/a/6958216
    friend class Money;


public:
    static std::string currencyTagNames[3];

    int rateInEuro;

    Money(int rateInEuro, long int value = 0);
    Money(int rateInEuro, Number value = Number(0));
    // TODO string constructor ?

    Number getRawValue() const
    {
        return this->value;
    }
    Number getMainValue() const
    {
        return this->value/100;    // TODO should be optimized as special function
    }
    int getCentsValue()
    {
        return this->value.getTwoLastDigits();
    }
    std::string getFormattedValue();
    std::string getStringName()
    {
        return currencyTagNames[static_cast<int>(T)];
    }


    // We only allow assignment within same currency - that's why Money<T>
    Money& operator=(Money<T> curr)
    {
        // TODO sprawdzenie czy nie przepisujemy samych siebie, test do tego
        this->value = curr.value;
        this->rateInEuro = curr.rateInEuro;
        return *this;
    }
    /* TODO
    Currency& operator-()
    {
        this->value = -value;
        return *this;
    }
    */
    template <currencyTag K>
    Money& operator+=(const Money<K> curr)
    {
        add(curr);
        return *this;
    }
    /* TODO
    Currency& operator-=(Currency curr)
    {
        add(-curr);
        return *this;
    }
    */
    Money& operator*=(const int m)
    {
        this->value = m * this->value;
        return *this;
    }

protected:
private:
    Number value;

    template<currencyTag K>

    // ASK how to move it to Money.cpp ?
    void add(Money<K> curr)
    {
        if(T == K )
            this->value +=curr.value;
        else
            this->value += curr.getInEuro()*this->rateInEuro;
    }

    Number getInEuro() const;
    currencyTag myTag;
};


template<currencyTag T1, currencyTag T2> inline bool operator==(const Money<T1>& c1, const Money<T2>& c2)
{
    return (T1 == T2 && c1.getRawValue() == c2.getRawValue()) ? true : false;
}
template<currencyTag T> inline Money<T> operator*(const int m, Money<T> c1)
{
    return c1*=m;
}
template<currencyTag T> inline Money<T> operator*(Money<T> c1, const int m)
{
    return c1*=m;
}
template<currencyTag T1, currencyTag T2> inline Money<T1> operator+(Money<T1> c1, const Money<T2>& c2)
{
    return c1+=c2;
}
/* TODO
inline Currency operator-( Currency c1, const Currency& c2)
{
    return c1-=c2;
}
*/

template class Money<currencyTag::PLN>; // TODO fixme ASK ???
template class Money<currencyTag::GBP>;



#endif // CURRENCY_H



