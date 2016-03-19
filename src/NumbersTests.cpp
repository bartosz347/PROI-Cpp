#include <boost/test/unit_test.hpp>

#include "Number.h"
#include <iostream>
#include <math.h>
#include <ctime>


BOOST_AUTO_TEST_SUITE(NumbersTests)

BOOST_AUTO_TEST_CASE( conversion_test )
{
   Number n(12998);
   BOOST_CHECK_EQUAL( n.tempGetString(),"12998");
}

BOOST_AUTO_TEST_CASE( addition )
{
    srand(time(0));
    for(int i = 0; i< 100000; i++)
    {
        {


        int ax = (std::rand() %100000),
    bx=std::rand() %100000;
    Number a(ax);
    Number b(bx);
    a += b;
    BOOST_CHECK_EQUAL(a.tempGetString(),std::to_string(ax+bx));
        }
    }


}


BOOST_AUTO_TEST_SUITE_END()
