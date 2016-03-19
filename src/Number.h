#ifndef NUMBERS_H_INCLUDED
#define NUMBERS_H_INCLUDED

#include <sstream>
#include <string>
#include <vector>
#include <math.h>

class Number
{
public:
    std::vector<char> t;

    Number(int number);

    std::string tempGetString() const;
    Number& operator+=(Number n)
    {
        int nIndex=0, selfIndex=0;
        carry = 0;
        while(nIndex < n.t.size() && selfIndex < t.size()) {
            addTwo2DigitNumbers(t[selfIndex], n.t[nIndex], carry);

            selfIndex++;
            nIndex++;
        }
        while(nIndex < n.t.size() ) {
            this->t.push_back(0);
            addTwo2DigitNumbers(t[selfIndex], n.t[nIndex], carry);
            selfIndex++;
            nIndex++;
        }
        while(selfIndex < t.size() ) {
            addTwo2DigitNumbers(t[selfIndex], 0, carry);
            selfIndex++;
        }
        if(carry > 0)
            this->t.push_back(carry);
        return *this;
    }

    void addTwo2DigitNumbers(char& a, char const b, char aCarry)
    {
        char ax = a;
        a = (a+b+aCarry)%100;
        carry = (ax+b+aCarry)/100;
    }


protected:
private:
    char carry;


};


#endif // NUMBERS_H_INCLUDED
