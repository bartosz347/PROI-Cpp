#include <boost/test/unit_test.hpp>

#include "Number.h"
#include <iostream>
#include <math.h>
#include <ctime>


// http://stackoverflow.com/questions/17572583/boost-check-fails-to-compile-operator-for-custom-types/17573165#17573165
// Changes made
namespace boost {
 namespace test_tools {
#ifdef __linux__
  template<>
  struct print_log_value<Number> {
#elif _WIN32
  struct print_log_value {
#endif // _WIN32
    void operator()( std::ostream& os, Number const& n)
    {
        ::operator<<(os, n);
    }
  };
 }
}

BOOST_AUTO_TEST_SUITE(NumbersTests)

BOOST_AUTO_TEST_CASE( string_constructor_1 )
{
    Number n{"123456"};
    BOOST_CHECK_EQUAL (n.to_string(), "123456");
}

BOOST_AUTO_TEST_CASE( string_constructor_short )
{
    Number n{"12"};
    BOOST_CHECK_EQUAL (n.to_string(), "12");
}

BOOST_AUTO_TEST_CASE( string_constructor_empty )
{
    Number n{""};
    BOOST_CHECK_EQUAL (n.to_string(), "0");
}

BOOST_AUTO_TEST_CASE( string_constructor_zeros )
{
    Number n{"000001"};
    BOOST_CHECK_EQUAL (n.to_string(), "1");
}

BOOST_AUTO_TEST_CASE( string_constructor_bad_data )
{
    BOOST_CHECK_THROW( {
                            Number n{"0g0"};
                       }, std::runtime_error);
}

BOOST_AUTO_TEST_CASE( addition_random )
{
    srand(time(0));
    for(int i = 0; i< 100; i++) {
        {
            int ax = (std::rand() %1000),
                bx=std::rand() %1000;
            Number a(ax);
            Number b(bx);
            a += b;
            BOOST_CHECK_EQUAL(a.to_string(),std::to_string(ax+bx));
        }
    }
}

BOOST_AUTO_TEST_CASE( addition_1 )
{
    Number a(9999);
    Number b(9999);
    a += b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(9999+9999));
}

BOOST_AUTO_TEST_CASE( addition_2 )
{
    Number a(9999);
    Number b(+99);
    a += b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(9999+99));
}

BOOST_AUTO_TEST_CASE( addition_3 )
{
    Number a(99);
    Number b(9999);
    a += b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(99+9999));
}

BOOST_AUTO_TEST_CASE( addition_4 )
{
    Number a(99997);
    Number b(5);
    a += b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(99997+5));
}

// TODO 999+9 -> zeby byla zmiana - dodanie bloku

BOOST_AUTO_TEST_CASE( addition_zero )
{
    Number a(99997);
    Number b(0);
    a += b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(99997));
}

BOOST_AUTO_TEST_CASE( multipl_simple )
{
    Number a(654981);
    a*=(11128);
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string((long long int)654981*11128));
    // std int64_t TODO
}

BOOST_AUTO_TEST_CASE( multipl_simple_zero )
{
    Number a(654981);
    a*=(0);
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string((long long int)654981*0));
}

BOOST_AUTO_TEST_CASE( multipl_1 )
{
    Number a(9999);
    Number b(9999);
    a *= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(9999*9999));
}

BOOST_AUTO_TEST_CASE( multipl_2 )
{
    Number a(99999);
    Number b(999);
    a *= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(99999*999));
}

BOOST_AUTO_TEST_CASE( multipl_3 )
{
    Number a(99);
    Number b(99999);
    a *= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(99*99999));
}

BOOST_AUTO_TEST_CASE( multipl_4 )
{
    Number a(9);
    Number b(9999);
    a *= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(9999*9));
}

BOOST_AUTO_TEST_CASE( multipl_by_zero )
{
    Number a(9);
    Number b(0);
    a *= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(9999*0));
}

BOOST_AUTO_TEST_CASE( multipl_zero )
{
    Number a(0);
    Number b(129);
    a *= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(0*129));
}

BOOST_AUTO_TEST_CASE( div_1 )
{
    Number a(68178);
    a /= 143;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(static_cast<int64_t>(68178/143)));
}

BOOST_AUTO_TEST_CASE( div_2 )
{
    Number a(150);
    a /= 200;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string((long int)150/200)); //TODO do not use this cast, use static cast!
}

BOOST_AUTO_TEST_CASE( div_zero_by )
{
    Number a(0);
    a /= 200;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string((long int)0));
}

BOOST_AUTO_TEST_CASE( div_by_zero_exception )
{
    Number a(150);
    BOOST_CHECK_THROW({a /= 0;}, std::runtime_error);
}

BOOST_AUTO_TEST_CASE( subtract_1 )
{
    Number a(68394);
    Number b(68310);
    a -= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(68394-68310));
}

BOOST_AUTO_TEST_CASE( subtract_zero )
{
    Number a(68394);
    Number b(0);
    a -= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(68394-0));
}

BOOST_AUTO_TEST_CASE( check_if_numbers_equal_true )
{
    Number a(68178);
    Number b(68178);
    Number c(178);

    BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE( check_if_numbers_equal_false )
{
    Number a(68178);
    Number c(178);

    BOOST_CHECK(!(a == c));
}

BOOST_AUTO_TEST_CASE( check_greater_than_true )
{
    Number a(12345);
    Number b(1234);

    BOOST_CHECK(a > b);
}

BOOST_AUTO_TEST_CASE( check_greater_than_false )
{
    Number a(12345);
    Number c(178);

    BOOST_CHECK(!(c > a));
}

BOOST_AUTO_TEST_CASE( get_decimals )
{
    Number a{68178};
    BOOST_CHECK_EQUAL(a.getDecimals(), 78);
}


BOOST_AUTO_TEST_SUITE_END()
