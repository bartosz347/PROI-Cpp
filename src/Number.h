#ifndef NUMBERS_H_INCLUDED
#define NUMBERS_H_INCLUDED

#include <sstream>
#include <string>
#include <vector>
#include <list>

#include <math.h>

class Number
{
public:
    std::list<char> digitCellsArr;
    Number(int number);

    std::string tempGetString();
    Number& operator+=(Number n)
    {
        std::list<char>::iterator nIter=n.digitCellsArr.begin(), selfIter=digitCellsArr.begin();

        carry = 0;
        while(nIter != n.digitCellsArr.end() && selfIter != digitCellsArr.end())
        {
            addTwo2DigitNumbers(*selfIter, *nIter, carry);
            nIter++;
            selfIter++;
        }

        while(nIter != n.digitCellsArr.end() )
        {
            selfIter--;
            this->digitCellsArr.push_back(0);
            selfIter++;

            addTwo2DigitNumbers(*selfIter, *nIter, carry);
            nIter++;
            selfIter++;
        }

        while(selfIter != digitCellsArr.end() )
        {
            addTwo2DigitNumbers(*selfIter, 0, carry);
            selfIter++;
        }
        if(carry > 0)
            this->digitCellsArr.push_back(carry);
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
