#ifndef CURRENCY_H
#define CURRENCY_H

#include "Number.h"
#include "MoneyConfig.h"
#include <string>






template <CurrencyTag T> class Money
{
    template<CurrencyTag K> // Lets us access private properties (like value)
                            //from all variations of Money http://stackoverflow.com/a/6958216
    friend class Money; // todo REMOVE
    // move 'comma' to number todo


public:
    Money(Number value = Number{0});
    int getEuroRate() const {
        return conf.CurrencyRates[static_cast<int>(T)];
    }



    template <CurrencyTag K>
    explicit operator Money<K>() const
    {
        Money<K> m = Money<K>{Number{0}};
        m += *this;
        return m;
    }
    Number getRawValue() const //return const reference TODO
    {
        return this->value;
    }
    Number getMainValue() const //return const reference TODO
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
        return conf.CurrencyTagNames[static_cast<int>(T)];
    }


    // We only allow assignment within same currency - that's why Money<T>
    // perf issues
    // implementacja operatorow tylko gdy mamy destruktor
    // rule of 5 (3) c++
    Money& operator=(Money<T> curr)
    {
        // TODO ASK sprawdzenie czy nie przepisujemy samych siebie, test do tego
        this->value = curr.value;

        return *this;
    }

    template <CurrencyTag K>
    Money& operator+=(const Money<K> money)
    {
        add(money);
        return *this;
    }

    template <CurrencyTag K>
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
    const static struct MoneyConfig conf;
    Number getInEuro() const;


    // ASK how to move it to Money.cpp ?
    template<CurrencyTag K>
    void add(Money<K> curr)
    {
        if(T == K)
            this->value +=curr.value;
        else
            this->value += curr.getInEuro()*this->getEuroRate();
    }

    template<CurrencyTag K>
    void subtract(Money<K> curr)
    {
        if(T == K)
            this->value -=curr.value;
        else
            this->value -= curr.getInEuro()*this->getEuroRate();
    }

};


template<CurrencyTag T1, CurrencyTag T2> inline bool operator==(const Money<T1>& c1, const Money<T2>& c2)
{
    return (T1 == T2 && c1.getRawValue() == c2.getRawValue()) ? true : false;
}
template<CurrencyTag T> inline Money<T> operator*(const int m, Money<T> c1)
{
    return c1*=m;
}
template<CurrencyTag T> inline Money<T> operator*(Money<T> c1, const int m)
{
    return c1*=m;
}
template<CurrencyTag T1, CurrencyTag T2> inline Money<T1> operator+(Money<T1> c1, const Money<T2>& c2)
{
    return c1+=c2;
}
template<CurrencyTag T1, CurrencyTag T2> inline Money<T1> operator-(Money<T1> c1, const Money<T2>& c2)
{
    return c1-=c2;
}


#endif // CURRENCY_H



