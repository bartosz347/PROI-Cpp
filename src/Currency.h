#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>
#include <math.h>

#include "Number.h"

enum currencyTag {PLN, GBP, USD};

//template <enum currencyTag > class Currency
class Currency
{
    public:
        std::string name;
        int rateInEuro;

        Currency(std::string name, double rateInEuro, long int value = 0);
        Currency(std::string name, int rateInEuro, long int value = 0);
       //TODO Currency(std::string name, int rateInEuro, Number value = Number(0));
        // TODO string constructor ?

        Number getRawValue() const { return this->value; }
        Number getMainValue() const { return this->value/100; } // TODO should be optimized as special function
        int getCentsValue() { return this->value.getTwoLastDigits(); }
        std::string getFormattedValue();

        Currency& operator=(Currency curr)
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
        Currency& operator+=(const Currency curr)
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
        Currency& operator*=(const int m)
        {
            this->value = m * this->value;
            return *this;
        }

    protected:
    private:
        Number value;
        void add(Currency curr);
        Number getInEuro() const;
};


inline bool operator==(const Currency& c1, const Currency& c2)
{
    return (c1.name.compare(c2.name) == 0 && c1.getRawValue() == c2.getRawValue()) ? true : false;
}
inline Currency operator*(const int m, Currency c1)
{
    return c1*=m;
}
inline Currency operator*(Currency c1, const int m)
{
    return c1*=m;
}
inline Currency operator+(Currency c1, const Currency& c2)
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



