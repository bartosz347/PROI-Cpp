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

        Currency& operator=(Currency curr) // referencja zbey mozna bylo uzyc a=b=c
        {
            // todo sprawdzenie czy nie przepisujemy samych siebie, test do tego!!, bo mozemy najpierw sie usunac a potem chciec odczyac to co usuniete
            this->name = curr.name;
            this->value = curr.value;
            this->rateInEuro = curr.rateInEuro;
            return *this;
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



