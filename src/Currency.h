#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>
#include <math.h>

enum currencyTag {PLN, GBP, USD};

//template <enum currencyTag > class Currency
class Currency
{
    public:
        std::string name;
        int rateInEuro;

        Currency(std::string name, double rateInEuro, int value = 0);
        Currency(std::string name, int rateInEuro, int value = 0);

        int getRawValue() const { return this->value; }
        int getMainValue() const { return this->value/100; }
        int getCentsValue() const { return this->value%100; }
        std::string getFormattedValue() const;

        Currency& operator=(Currency curr)
        {
            // TODO sprawdzenie czy nie przepisujemy samych siebie, test do tego
            this->name = curr.name;
            this->value = curr.value;
            this->rateInEuro = curr.rateInEuro;
            return *this;
        }
        Currency& operator-()
        {
            this->value = -value;
            return *this;
        }
        Currency& operator+=(const Currency curr)
        {
            add(curr);
            return *this;
        }
        Currency& operator-=(Currency curr)
        {
            add(-curr);
            return *this;
        }
        Currency& operator*=(const int m)
        {
            this->value = m * this->value;
            return *this;
        }

    protected:
    private:
        long int value;
        void add(Currency curr);
        long int getInEuro() const;
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
inline Currency operator-( Currency c1, const Currency& c2)
{
    return c1-=c2;
}

#endif // CURRENCY_H



