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
    Number(long int number = 0);


    std::string to_string() const;

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
    int getTwoLastDigits()
    {
        return *(digitCellsArr.begin()) % 100;
    }


protected:
private:
    int carry;


};

bool operator==(Number n1, Number n2);

inline Number& operator/(Number n, const int a)
{
    return n/=a;
}

inline Number& operator*( const int a, Number n)
{
    return n*=a;
}

inline Number& operator*(Number n, const int a)
{
    return n*=a;
}

inline std::string to_string(Number n)
{
    return n.to_string();
}

static inline std::ostream& operator<< (std::ostream& os, const Number& n)
{
    os << n.to_string();
    return os;
}





#endif // NUMBERS_H_INCLUDED
