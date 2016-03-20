#include "Number.h"


Number::Number(int number)
{
    if(number == 0) {
        digitCellsArr.push_back(0);
    }
    while(number != 0) {
        digitCellsArr.push_back(number % 100);
        number /= 100;
    }
}

std::string Number::tempGetString()
{
    std::stringstream s;
    std::list<char>::reverse_iterator rIter = digitCellsArr.rbegin(); // reverse iterator!
    s << std::to_string(*rIter) ;
    rIter++;
    for(; rIter != digitCellsArr.rend(); rIter++) {
       if(*rIter > 9)
             s << std::to_string(*rIter);
       else
            s<< "0"+std::to_string(*rIter);
    }
    std::string ret;
    s >> ret;
    return ret;
}
