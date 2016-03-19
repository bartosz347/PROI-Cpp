#ifndef CURRENCYOPERATORS_H_INCLUDED
#define CURRENCYOPERATORS_H_INCLUDED

#include "Currency.h"

bool operator==(const Currency c1, const Currency c2) { return c1.name.compare(c2.name) == 0 ? true : false; }
Currency operator*(const int m, Currency c1) {return c1*=m;}
Currency operator*(Currency c1, const int m) {return c1*=m;}
Currency operator+(Currency c1, const Currency c2) {return c1+=c2;} //todo pass c2 as reference - strings uses memory...
inline Currency operator-( Currency c1, const Currency c2) {return c1-=c2;} // todo all above should be inline - jesli bedziemy potem to includowali, bez inline - kompilator przeklei do kodu i będzie wiele definicji tego samego


// odo should be in Currency .cpp(?), not in separate file!

#endif // CURRENCYOPERATORS_H_INCLUDED
