#ifndef NUMBERS_H_INCLUDED
#define NUMBERS_H_INCLUDED

#include <sstream>
#include <string>
#include <list>

#define BASE 1000
#define DIGITS 3

class Number
{
public:
    std::list<int> digitCellsArr;
    Number(long int number);

    std::string tempGetString();

    Number& operator+=(Number n);
    Number& operator*=(int a);
    Number& operator*=(const Number n);
    Number& operator/=(const int a);


    void addTwo2DigitNumbers(int& a, int const b, int aCarry)
    {
        int ax = a;
        a = (a+b+aCarry)%BASE;
        carry = (ax+b+aCarry)/BASE;
    }


protected:
private:
    int carry;


};


#endif // NUMBERS_H_INCLUDED
