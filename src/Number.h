#ifndef NUMBERS_H_INCLUDED
#define NUMBERS_H_INCLUDED

#include <sstream>
#include <string>
#include <list>
#include <stdexcept>
#include <regex>

class Number
{
public:
    std::list<int> digitCellsArr;
    Number(long int number = 0);
    Number(std::string numberString); // todo make explicit n+="xyz"!

    std::string to_string() const;

    Number& operator+=(Number n);
    Number& operator*=(int a);
    Number& operator*=(const Number n);
    Number& operator/=(const int a);
    Number& operator-=(const Number n);


    void trimZeros()
    {
        std::list<int>::reverse_iterator selfIter = digitCellsArr.rbegin();
        bool wasFirstZero = *(digitCellsArr.begin()) == 0 ? true: false;

        while(selfIter != digitCellsArr.rend() && digitCellsArr.size() > 0) {
            if(*selfIter == 0) {
                selfIter++;
                digitCellsArr.pop_back();
            } else
                return;
        }
        if(wasFirstZero && digitCellsArr.size() == 0)
            digitCellsArr.push_back(0);
    }

    void addTwo2DigitNumbers(int& a, int const b, int aCarry)
    {
        int ax = a;
        a = (a+b+aCarry)%BASE;
        carry = (ax+b+aCarry)/BASE;
    }
    int getTwoLastDigits() const
    {
        return *(digitCellsArr.begin()) % 100;
    }


protected:
private:
    static const int DIGITS = 3;
    static const int BASE = 1000;

    int carry;


};

bool operator==(Number n1, Number n2);
bool operator>(Number n1, Number n2);

inline Number& operator/(Number n, const int a) // TODO nie przez referencje - n znika po wyjsciu z funkcji
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
inline Number& operator-(Number n1, Number n2)
{
    return n1-=n2;
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
