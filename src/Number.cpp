#include "Number.h"


Number::Number(long int number)
{
    if(number == 0) {
        digitCellsArr.push_back(0);
    }
    if(number < 0) {
        number = -number;
        isNegative = true;
    }
    while(number != 0) {
        digitCellsArr.push_back(number % BASE);
        number /= BASE;
    }
}

Number::Number(std::string numberString)
{
    //TODO problem gcc version? And problem with C++11 vs boost version...
    #ifndef BOOST_REGEX
        const std::regex digitsRegex{"^-?[0-9]*$"};
        if(!std::regex_match(numberString, digitsRegex))
    #else
        const boost::regex digitsRegex("^-?[0-9]*$");
        boost::smatch str_matches;
        if(!boost::regex_match(numberString, digitsRegex))
    #endif
           throw std::runtime_error{"string contains characters other than digits and minus"};
    int length = numberString.size();
    if(length == 0) {
        digitCellsArr.push_back(0);
        return;
    }
    if(numberString.front() == '-') {
        numberString.erase(0,1);
        isNegative = true;
        length--;
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
    std::vector<int>::const_reverse_iterator rIter = digitCellsArr.crbegin(); // reverse iterator!
    if(isNegative) s << "-";
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
    if(!addingAbs) {
        if(!isNegative && n.isNegative) {

                 this->isNegative=false;
         n.isNegative=false;
            return *this-=n;
        }
         if(isNegative && !n.isNegative) {
                n.isNegative=true;
                this->isNegative=false;
            return  *this -=n;
         }
        //setSignAddition(*this, n);
    }

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
    addingAbs=false;
    return *this;
}


Number& Number::operator*=(int a)
{
    setSignDivMult(*this, a);
    if(a<0) a = -a;
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
    setSignDivMult(*this, n);
    const Number mCopy_const = *this;
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


Number& Number::operator/=(int a)
{
    setSignDivMult(*this, a);
    if(a<0) a = -a;
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
 void Number::setSignAddition(const Number &a, const Number &b)
    {
        if(a.isNegative && b.isNegative)
            isNegative = true;
        else if(!a.isNegative && !b.isNegative)
            isNegative = false;
        else if(!a.isNegative)
            if(a > b)
                isNegative = false;
            else
                isNegative = true;
        else
            if(a>b)
                isNegative = true;
            else
                isNegative = false;
    }


Number& Number::operator-=(Number n)
{
    if(isNegative && !n.isNegative) {
        addingAbs=true;
        isNegative=true;
        return *this+=n;

    } //OK

    if(!isNegative && n.isNegative) {
        addingAbs=true;
        isNegative=false;
        return *this+=n;
    } //OK
   if(n.isNegative && isNegative)
   {
       Number tmp = *this;
       *this = n;
       n = tmp;
       this->isNegative=false;
       n.isNegative = false;
   }// OK
   /*else

   if(this->isNegative && !n.isNegative) {
        Number tmp = *this;
        *this = n;
        n = tmp;
        isNegative = false;
        n.isNegative  = false;
        addingAbs=true; }
*/
  else if(n > *this) {
        Number tmp = *this;
        *this = n;
        n = tmp;
        isNegative = true;
   }



   //
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

    for(auto n1_Iter=n1.digitCellsArr.cbegin(), n2_Iter=n2.digitCellsArr.cbegin(); n1_Iter != n1.digitCellsArr.cend() && n2_Iter != n2.digitCellsArr.cend(); )
    {
        if(*n1_Iter != *n2_Iter)
            return false;
        n2_Iter++;
        n1_Iter++;
    }
    return true;
}


bool operator>(const Number& n1, const Number& n2)
{
    if(n1.digitCellsArr.size() > n2.digitCellsArr.size()) // negative todo
        return true;
    else if( n1.digitCellsArr.size() < n2.digitCellsArr.size())
        return false;

    for(auto n1_Iter=n1.digitCellsArr.crbegin(), n2_Iter=n2.digitCellsArr.crbegin(); n1_Iter != n1.digitCellsArr.crend() && n2_Iter != n2.digitCellsArr.crend(); )
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



