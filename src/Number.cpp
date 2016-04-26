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

Number::Number(std::string numberString)
{
   int length = numberString.size();
    if(length == 0) {
        digitCellsArr.push_back(0);
        return;
    }
    int posInString = length - DIGITS;
    while(posInString > 0) {
        digitCellsArr.push_back(std::stoi(numberString.substr(posInString, DIGITS)));
        posInString -= DIGITS;
    }
    if(posInString < 0)
        posInString += DIGITS;
    else
        posInString = DIGITS;
    digitCellsArr.push_back(std::stoi(numberString.substr(0, posInString)));
    trimZeros();
}


std::string Number::to_string() const
{
    std::stringstream s;
    std::string ret;
    std::list<int>::const_reverse_iterator rIter = digitCellsArr.crbegin(); // reverse iterator!
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
    trimZeros();
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
    if(a == 0) throw std::runtime_error{"div by 0"};
    if(*this == 0) return *this;
    int carry = 0;
    bool nonzeroSeen = false;
    int elementToRemoveNo = 0;

    for(std::list<int>::reverse_iterator rSelfIter = digitCellsArr.rbegin(); rSelfIter != digitCellsArr.rend(); rSelfIter++) {
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
    trimZeros();
    return *this;
}


Number& Number::operator-=(Number n)
{
    if(n > *this) {
        throw std::runtime_error{"negative numbers are not supported"};
        digitCellsArr.clear();
        return *this;
    }

    std::list<int>::iterator nIter = n.digitCellsArr.begin(),
                             selfIter = digitCellsArr.begin(),
                             tmpIter;

    while(nIter != n.digitCellsArr.end()) {
        if(*selfIter < *nIter) {
            tmpIter = selfIter;
            tmpIter++;
            --*tmpIter;
            *(selfIter) -= *nIter;
            *(selfIter) += BASE;
        }
        else {
            *(selfIter) -= *nIter;
        }
        nIter++;
        selfIter++;
    }

    trimZeros();
    return *this;
}


bool operator==(Number n1, Number n2)
{
    if(n1.digitCellsArr.size() != n2.digitCellsArr.size())
        return false;

    for(std::list<int>::iterator n1_Iter=n1.digitCellsArr.begin(), n2_Iter=n2.digitCellsArr.begin(); n1_Iter != n1.digitCellsArr.end() && n2_Iter != n2.digitCellsArr.end(); )
    {
        if(*n1_Iter != *n2_Iter)
            return false;
        n2_Iter++;
        n1_Iter++;
    }
    return true;
}


bool operator>(Number n1, Number n2)
{
    if(n1.digitCellsArr.size() > n2.digitCellsArr.size()) // negative
        return true;
    else if( n1.digitCellsArr.size() < n2.digitCellsArr.size())
        return false;

    for(std::list<int>::reverse_iterator n1_Iter=n1.digitCellsArr.rbegin(), n2_Iter=n2.digitCellsArr.rbegin(); n1_Iter != n1.digitCellsArr.rend() && n2_Iter != n2.digitCellsArr.rend(); )
    {
        if(*n1_Iter > *n2_Iter)
            return true;
        else if(*n1_Iter < *n2_Iter)
            return false;
        n2_Iter++;
        n1_Iter++;
    }
    return false;
}



