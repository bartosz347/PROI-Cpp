#include "Number.h"


Number::Number(long int number)
{
    if(number == 0) {
        digitCellsArr.push_back(0);
    }
    while(number != 0) {
        digitCellsArr.push_back(number % BASE);
        number /= BASE;
    }
}

std::string Number::tempGetString()
{
    std::stringstream s;
    std::string ret;
    std::list<int>::reverse_iterator rIter = digitCellsArr.rbegin(); // reverse iterator!
    if(*rIter == 0 && digitCellsArr.size() == 1) {
        s << "0";
        s >> ret;
        return ret;
    }
    s << std::to_string(*rIter);
    rIter++;

    for(; rIter != digitCellsArr.rend(); rIter++) {
        int noZeros = DIGITS;
        int cellTemp = *rIter;
        while(cellTemp != 0) {
            cellTemp /= 10;
            noZeros--;
        }
        for(; noZeros > 0; noZeros--)
            s << "0";
        if(*rIter != 0)
            s << std::to_string(*rIter);
    }

    s >> ret;
    return ret;
}

Number& Number::operator+=(Number n)
{
    std::list<int>::iterator nIter=n.digitCellsArr.begin(), selfIter=digitCellsArr.begin();

    carry = 0;
    while(nIter != n.digitCellsArr.end() && selfIter != digitCellsArr.end()) {
        addTwo2DigitNumbers(*selfIter, *nIter, carry);
        nIter++;
        selfIter++;
    }

    while(nIter != n.digitCellsArr.end() ) {
        selfIter--;
        this->digitCellsArr.push_back(0);
        selfIter++;

        addTwo2DigitNumbers(*selfIter, *nIter, carry);
        nIter++;
        selfIter++;
    }

    while(selfIter != digitCellsArr.end() ) {
        addTwo2DigitNumbers(*selfIter, 0, carry);
        selfIter++;
    }
    if(carry > 0)
        this->digitCellsArr.push_back(carry);
    return *this;
}


Number& Number::operator*=(int a)
{
    int carry = 0;

    for(std::list<int>::iterator selfIter=digitCellsArr.begin(); selfIter != digitCellsArr.end(); selfIter++) {
        long int t = *selfIter*a + carry;
        *selfIter = t % BASE;
        carry = t/BASE;
    }
    if(carry > 0) {
        digitCellsArr.push_back(carry);
    }
    return *this;
}

Number& Number::operator*=(Number n)
{
    const Number mCopy_const = *this;
    Number mCopy = mCopy_const;
    this->digitCellsArr.clear();
    int i = 0;
    for(std::list<int>::iterator nIter=n.digitCellsArr.begin(); nIter != n.digitCellsArr.end(); nIter++) {
        mCopy *= *nIter;

        for(int j = i; j > 0; j--) {
            mCopy.digitCellsArr.push_front(0);
        }
        i ++;
        *this += mCopy;
        mCopy = mCopy_const;
    }
    return *this;
}

Number& Number::operator/=(const int a)
{
    if(a == 0) return *this;
    int carry = 0;
    bool nonzeroSeen = false;
    int elementToRemoveNo = 0;

    for(std::list<int>::reverse_iterator rSelfIter=digitCellsArr.rbegin(); rSelfIter != digitCellsArr.rend(); rSelfIter++) {
        *rSelfIter += carry * BASE;
        carry = *rSelfIter % a;
        *rSelfIter /= a;
        if(!nonzeroSeen && *rSelfIter == 0) {
            elementToRemoveNo++;
        } else if(*rSelfIter != 0)
            nonzeroSeen = true;
    }

    for(; elementToRemoveNo > 0; elementToRemoveNo--)
        digitCellsArr.pop_back();
    return *this;
}


