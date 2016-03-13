#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>
#include <math.h>

class Currency
{
    public:
        Currency(std::string name, double rateInEuro, int value = 0);

        std::string name;

        int getMainValue() { return this->value/100; }
        int getCentsValue() { return this->value%100; }
        std::string getFormattedValue();

        void multiply(int m);
        long int getMultiplied(int);
        void add(Currency curr);
        long int getSum(Currency curr);
        void assign(Currency curr);
        bool isInSameCurrency(Currency curr) { return this->name.compare(curr.name) == 0 ? true :false; }

        #ifdef DEBUG
            int getRateInEuro() { return this->rateInEuro; }
            int getRawValue() { return this->value; }
        #endif
    protected:
    private:
        long int value;
        int rateInEuro;
        getInEuro();
};

#endif // CURRENCY_H
