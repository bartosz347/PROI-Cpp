#include <boost/test/unit_test.hpp>

#include "Number.h"
#include <iostream>
#include <math.h>
#include <ctime>


BOOST_AUTO_TEST_SUITE(NumbersTests)

BOOST_AUTO_TEST_CASE( conversion_test )
{
    srand(time(0));
    for(int i = 0; i < 10; i++) {
        {
            int k = (std::rand() %100000);
            Number n(k);
            BOOST_CHECK_EQUAL( n.tempGetString(), std::to_string(k));
        }
    }
}

BOOST_AUTO_TEST_CASE( addition_random )
{

    srand(time(0));
    for(int i = 0; i< 100000; i++) {
        {
            int ax = (std::rand() %1000),
                bx=std::rand() %1000;
            Number a(ax);
            Number b(bx);
            a += b;
            BOOST_CHECK_EQUAL(a.tempGetString(),std::to_string(ax+bx));
        }
    }
}

BOOST_AUTO_TEST_CASE( addition_1 )
{
    Number a(9999);
    Number b(9999);
    a += b;
    BOOST_CHECK_EQUAL(a.tempGetString(),std::to_string(9999+9999));
}

BOOST_AUTO_TEST_CASE( addition_2 )
{
    Number a(9999);
    Number b(+99);
    a += b;
    BOOST_CHECK_EQUAL(a.tempGetString(),std::to_string(9999+99));
}

BOOST_AUTO_TEST_CASE( addition_3 )
{
    Number a(99);
    Number b(9999);
    a += b;
    BOOST_CHECK_EQUAL(a.tempGetString(),std::to_string(99+9999));
}

BOOST_AUTO_TEST_CASE( addition_4 )
{
    Number a(99997);
    Number b(5);
    a += b;
    BOOST_CHECK_EQUAL(a.tempGetString(),std::to_string(99997+5));
}

BOOST_AUTO_TEST_CASE( multipl_simple )
{
    Number a(654981);
    a*=(11128);
    BOOST_CHECK_EQUAL(a.tempGetString(),std::to_string((long long int)654981*11128));
}


BOOST_AUTO_TEST_CASE( multipl_1 )
{
    Number a(9999);
    Number b(9999);
    a *= b;
    BOOST_CHECK_EQUAL(a.tempGetString(),std::to_string(9999*9999));
}

BOOST_AUTO_TEST_CASE( multipl_2 )
{
    Number a(99999);
    Number b(999);
    a *= b;
    BOOST_CHECK_EQUAL(a.tempGetString(),std::to_string(99999*999));
}

BOOST_AUTO_TEST_CASE( multipl_3 )
{
    Number a(99);
    Number b(99999);
    a *= b;
    BOOST_CHECK_EQUAL(a.tempGetString(),std::to_string(99*99999));
}

BOOST_AUTO_TEST_CASE( multipl_4 )
{
    Number a(9);
    Number b(9999);
    a *= b;
    BOOST_CHECK_EQUAL(a.tempGetString(),std::to_string(9999*9));
}

BOOST_AUTO_TEST_CASE( div_1 )
{
    Number a(68178);
    a /= 143;
    BOOST_CHECK_EQUAL(a.tempGetString(),std::to_string((long int)68178/143));
}


BOOST_AUTO_TEST_SUITE_END()
