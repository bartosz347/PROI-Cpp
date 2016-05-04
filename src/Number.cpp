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
//TODO problem gcc version?

    #ifndef BOOST_REGEX
        const std::regex digitsRegex{"^[0-9]*$"};
        if(!std::regex_match(numberString, digitsRegex))
    #elif
        const boost::regex digitsRegex("^[0-9]*$");
        if(boost::regex_match(numberString, digitsRegex) == false)
    #endif
            throw std::runtime_error{"string contains characters other than digits and blank"};
    int length = numberString.size();
    if(length == 0) {
        digitCellsArr.push_back(0);
        return;
    }
    int posInString = length - DIGITS; // no defines -> static const TODO
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
    std::vector<int>::const_reverse_iterator rIter = digitCellsArr.crbegin(); // reverse iterator!
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
    int nIndex = 0, selfIndex = 0;
    int nSize = n.digitCellsArr.size(), selfSize = digitCellsArr.size();

    carry = 0;
    while(nIndex < nSize && selfIndex < selfSize) {
        addTwo2DigitNumbers(digitCellsArr[selfIndex], n.digitCellsArr[nIndex], carry);
        nIndex++;
        selfIndex++;
    }

    while(nIndex < nSize) {
        selfIndex--;
        this->digitCellsArr.push_back(0);
        selfIndex++;

        addTwo2DigitNumbers(digitCellsArr[selfIndex],  n.digitCellsArr[nIndex], carry);
        nIndex++;
        selfIndex++;
    }

    nSize = n.digitCellsArr.size(), selfSize = digitCellsArr.size();

    while(selfIndex < selfSize ) {
        addTwo2DigitNumbers(digitCellsArr[selfIndex], 0, carry);
        selfIndex++;
    }
    if(carry > 0)
        this->digitCellsArr.push_back(carry);
    return *this;
}


Number& Number::operator*=(int a)
{
    int carry = 0;
    for(unsigned int selfIndex = 0; selfIndex < digitCellsArr.size(); selfIndex++) {
        long int t = digitCellsArr[selfIndex]*a + carry;
        digitCellsArr[selfIndex] = t % BASE;
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
    const Number mCopy_const = *this; // TODO??
    Number mCopy = mCopy_const;
    this->digitCellsArr.clear();
    int i = 1, nSize = n.digitCellsArr.size();
    for(int nIndex = 0; nIndex < nSize; nIndex++) {
        mCopy *= n.digitCellsArr[nIndex];
        *this += mCopy;
        i *= BASE;
        mCopy = mCopy_const*i;
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

    for(std::vector<int>::reverse_iterator rSelfIter = digitCellsArr.rbegin(); rSelfIter != digitCellsArr.rend(); rSelfIter++) {
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

    std::vector<int>::iterator nIter = n.digitCellsArr.begin(),
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

    for(std::vector<int>::iterator n1_Iter=n1.digitCellsArr.begin(), n2_Iter=n2.digitCellsArr.begin(); n1_Iter != n1.digitCellsArr.end() && n2_Iter != n2.digitCellsArr.end(); )
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

    for(std::vector<int>::reverse_iterator n1_Iter=n1.digitCellsArr.rbegin(), n2_Iter=n2.digitCellsArr.rbegin(); n1_Iter != n1.digitCellsArr.rend() && n2_Iter != n2.digitCellsArr.rend(); )
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



