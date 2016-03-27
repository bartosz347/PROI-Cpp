#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>
#include <math.h>

#include "Number.h"

enum currencyTag {PLN, GBP, USD};

//template < enum currencyTag > class Money
class Money
{
    public:
        std::string name;
        int rateInEuro;

        Money(std::string name, double rateInEuro, long int value = 0);
        Money(std::string name, int rateInEuro, long int value = 0);
       //TODO Currency(std::string name, int rateInEuro, Number value = Number(0));
        // TODO string constructor ?

        Number getRawValue() const { return this->value; }
        Number getMainValue() const { return this->value/100; } // TODO should be optimized as special function
        int getCentsValue() { return this->value.getTwoLastDigits(); }
        std::string getFormattedValue();

        Money& operator=(Money curr)
        {
            // TODO sprawdzenie czy nie przepisujemy samych siebie, test do tego
            this->name = curr.name;
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
        Money& operator+=(const Money curr)
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
        void add(Money curr);
        Number getInEuro() const;
};


inline bool operator==(const Money& c1, const Money& c2)
{
    return (c1.name.compare(c2.name) == 0 && c1.getRawValue() == c2.getRawValue()) ? true : false;
}
inline Money operator*(const int m, Money c1)
{
    return c1*=m;
}
inline Money operator*(Money c1, const int m)
{
    return c1*=m;
}
inline Money operator+(Money c1, const Money& c2)
{
    return c1+=c2;
}
/* TODO
inline Currency operator-( Currency c1, const Currency& c2)
{
    return c1-=c2;
}
*/






#endif // CURRENCY_H



