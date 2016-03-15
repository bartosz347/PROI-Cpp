#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>
#include <math.h>

class Currency
{
    public:
        std::string name;
        int rateInEuro;

        Currency(std::string name, double rateInEuro, int value = 0);
        Currency(std::string name, int rateInEuro, int value = 0);

        int getRawValue() { return this->value; }
        int getMainValue() const { return this->value/100; }
        int getCentsValue() const { return this->value%100; }
        std::string getFormattedValue() const;

        void operator=(Currency curr)
        {
            this->name = curr.name;
            this->value = curr.value;
            this->rateInEuro = curr.rateInEuro;
        }
        Currency& operator-() {this->value = -value; return *this;}
        Currency& operator+=(const Currency curr) { add(curr); return *this; }
        Currency& operator-=(Currency curr) { add(-curr); return *this; }
        Currency& operator*=(const int m) {  this->value = m * this->value; return *this; }

    protected:
    private:
        long int value;
        void add(Currency curr);
        long int getInEuro() const;
};


#endif // CURRENCY_H



