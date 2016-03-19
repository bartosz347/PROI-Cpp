#include "Number.h"


Number::Number(int number)
{
    if(number == 0) {
        t.push_back(0);
    }
    while(number != 0) {
        t.push_back(number % 100);
        number /= 100;
    }
}

std::string Number::tempGetString() const
{
    std::stringstream s;
    s << std::to_string(t[t.size()-1]) ;
    for(int i = t.size()-2; i >= 0; i--) {
       if(t[i] > 9)
             s <<  std::to_string(t[i]) ;
       else
            s<< "0"+std::to_string(t[i]);
       // s <<  std::to_string(t[i]) ;
    }
    std::string ret;
    s >> ret;
    return ret;
}
