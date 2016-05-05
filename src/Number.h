#ifndef NUMBERS_H_INCLUDED
#define NUMBERS_H_INCLUDED

#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <regex>



class Number {
    friend bool operator==(Number n1, Number n2);
    friend bool operator>(const Number& n1, const Number& n2);
public:
    Number(std::string numberString); // explicit to avoid n+="xyz" ASK TODO
    Number(long int number = 0);

    std::string to_string() const;

    Number& operator+=(Number n);
    Number& operator*=(int a);
    Number& operator*=(const Number n);
    Number& operator/=(const int a);
    Number& operator-=(const Number n);

    int getDecimals() const
    {
        return *(digitCellsArr.begin()) % (MAX_DECIMALS_VALUE+1);
    }

protected:
private:
    std::vector<int> digitCellsArr;
    static const int DIGITS = 3;
    static const int BASE = 1000;
    static const int MAX_DECIMALS_VALUE = 99;

    int carry;
    bool isNegative = false;
    bool addingAbs=false;

    void setSignDivMult(const Number &a, const Number &b)
    {
        if(a.isNegative && b.isNegative)
            isNegative = false;
        else if(!a.isNegative && !b.isNegative)
            isNegative = false;
        else
            isNegative = true;
    }

    void trimZeros()
    {
        std::vector<int>::reverse_iterator selfIter = digitCellsArr.rbegin();
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
};



inline Number operator/(Number n, const int a)
{
    return n/=a;
}

inline Number operator*( const int a, Number n)
{
    return n*=a;
}

inline Number operator*(Number n, const int a)
{
    return n*=a;
}
inline Number operator-(Number n1, Number n2)
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


bool operator>(const Number& n1, const Number& n2);
bool operator==(Number n1, Number n2);

#endif // NUMBERS_H_INCLUDED
