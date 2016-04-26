#ifndef CURRENCY_H
#define CURRENCY_H

#include "Number.h"
#include <string>

#define CURRENCIES PLN,GBP,USD
#define CURRENCIES_STRING "PLN","GBP","USD"
#define CURRENCIES_RATES 400,200,300
#define CURRENCIES_NO 3

#define DECIMAL_SEPARATOR "."
#define CURRENCY_SEPARATOR " "

enum class currencyTag
{
    CURRENCIES
};


template <currencyTag T> class Money
{
    template<currencyTag K> // Lets us access private properties (like value)
                            //from all variations of Money http://stackoverflow.com/a/6958216
    friend class Money;


public:
    static std::string currencyTagNames[CURRENCIES_NO];
    static int currencyRates[CURRENCIES_NO];

    int rateInEuro;

    Money(long int value);
    Money(Number value = Number{0});
    Money(std::string numberString);


    template <currencyTag K>
    explicit operator Money<K>() const
    {
        Money<K> m = Money<K>{Number{0}};
        m += *this;
        return m;
    }
    Number getRawValue() const
    {
        return this->value;
    }
    Number getMainValue() const
    {
        return this->value/100;
    }
    int getCentsValue() const
    {
        return this->value.getTwoLastDigits();
    }
    std::string toString() const;
    std::string getStringName() const
    {
        return currencyTagNames[static_cast<int>(T)];
    }


    // We only allow assignment within same currency - that's why Money<T>
    Money& operator=(Money<T> curr)
    {
        // TODO ASK sprawdzenie czy nie przepisujemy samych siebie, test do tego
        this->value = curr.value;
        this->rateInEuro = curr.rateInEuro;
        return *this;
    }

    template <currencyTag K>
    Money& operator+=(const Money<K> money)
    {
        add(money);
        return *this;
    }

    template <currencyTag K>
    Money& operator-=(const Money<K> money)
    {
        subtract(money);
        return *this;
    }

    Money& operator*=(const int m)
    {
        this->value = m * this->value;
        return *this;
    }

protected:
private:
    Number value;

    // ASK how to move it to Money.cpp ?
    template<currencyTag K>
    void add(Money<K> curr)
    {
        if(T == K)
            this->value +=curr.value;
        else
            this->value += curr.getInEuro()*this->rateInEuro;
    }

    template<currencyTag K>
    void subtract(Money<K> curr)
    {
        if(T == K)
            this->value -=curr.value;
        else
            this->value -= curr.getInEuro()*this->rateInEuro;
    }

    Number getInEuro() const;
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
template<currencyTag T1, currencyTag T2> inline Money<T1> operator-(Money<T1> c1, const Money<T2>& c2)
{
    return c1-=c2;
}

template class Money<currencyTag::PLN>; // TODO fixme ASK
template class Money<currencyTag::GBP>;



#endif // CURRENCY_H



