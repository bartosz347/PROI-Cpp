#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>

class Currency
{
    public:
        Currency(std::string name, int rateInEuro, int value = 0);

        multiply(int m);
        void setValue(long int value)
        {

        }
    protected:
    private:
        std::string name;
        long int value;
        int rateInEuro;
};

#endif // CURRENCY_H
