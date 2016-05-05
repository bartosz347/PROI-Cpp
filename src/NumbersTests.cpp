#include <boost/test/unit_test.hpp>

#include "Number.h"
#include <iostream>
#include <math.h>
#include <ctime>


// http://stackoverflow.com/questions/17572583/boost-check-fails-to-compile-operator-for-custom-types/17573165#17573165
// Changes made
namespace boost
{
namespace test_tools
{
#ifdef __linux__
template<>
struct print_log_value<Number>
{
#elif _WIN32
struct print_log_value
{
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
    BOOST_CHECK_THROW(
    {
        Number n{"0g0"};
    }, std::runtime_error);
}

BOOST_AUTO_TEST_CASE( string_constructor_negative )
{
    Number n{"-666"};
    BOOST_CHECK_EQUAL (n.to_string(), "-666");
}

BOOST_AUTO_TEST_CASE( int_constructor_negative )
{
    Number n{-123456};
    BOOST_CHECK_EQUAL (n.to_string(), "-123456");
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
    Number b(99);
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

BOOST_AUTO_TEST_CASE( addition_zero )
{
    Number a(99997);
    Number b(0);
    a += b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(99997));
}

BOOST_AUTO_TEST_CASE( addition_negative_first )
{
    Number a(-125);
    Number b(250);
    a += b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(-125+250));
}

BOOST_AUTO_TEST_CASE( addition_negative_second )
{
    Number a(125);
    Number b(-250);
    a += b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(125-250));
}

BOOST_AUTO_TEST_CASE( addition_negative_both )
{
    Number a(-125);
    Number b(-950);
    a += b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(-950-125));
}

BOOST_AUTO_TEST_CASE( multipl_simple )
{
    Number a(654981);
    a*=(1112);
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(static_cast<uint64_t>(654981*1112)));
}

BOOST_AUTO_TEST_CASE( multipl_simple_zero )
{
    Number a(654981);
    a*=(0);
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string((long long int)654981*0));
}

BOOST_AUTO_TEST_CASE( multipl_simple_negative_1 )
{
    Number a(500);
    a*=(-2);
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(-2*500));
}

BOOST_AUTO_TEST_CASE( multipl_simple_negative_2 )
{
    Number a(-500);
    a*=(2);
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(-2*500));
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

BOOST_AUTO_TEST_CASE( multipl_negative_1 )
{
    Number a(-30);
    Number b(1000);
    a *= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(-30*1000));
}

BOOST_AUTO_TEST_CASE( multipl_negative_2 )
{
    Number a(30);
    Number b(-1000);
    a *= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(-30*1000));
}

BOOST_AUTO_TEST_CASE( multipl_negative_3 )
{
    Number a(-30);
    Number b(-1000);
    a *= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(-30*-1000));
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
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(static_cast<int64_t>(150/200)));
}

BOOST_AUTO_TEST_CASE( div_zero_by )
{
    Number a(0);
    a /= 200;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(0));
}

BOOST_AUTO_TEST_CASE( div_by_zero_exception )
{
    Number a(150);
    BOOST_CHECK_THROW({a /= 0;}, std::runtime_error);
}

BOOST_AUTO_TEST_CASE( div_negative_first )
{
    Number a(-450);
    a /= 5;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(450/-5));
}

BOOST_AUTO_TEST_CASE( div_negative_second )
{
    Number a(450);
    a /= -5;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(450/-5));
}

BOOST_AUTO_TEST_CASE( div_negative_both )
{
    Number a(-450);
    a /= -5;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(-450/-5));
}

BOOST_AUTO_TEST_CASE( subtract_positive_res )
{
    Number a(68394);
    Number b(68310);
    a -= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(68394-68310));
}

BOOST_AUTO_TEST_CASE( subtract_negative_result )
{
    Number a(946);
    Number b(9846);
    a -= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(946-9846));
}

BOOST_AUTO_TEST_CASE( subtract_1 )
{
    Number a(946);
    Number b(9846);
    a -= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(946-9846));
}

BOOST_AUTO_TEST_CASE( subtract_2 )
{
    Number a(-946);
    Number b(-9846);
    a -= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(-946+9846));
}

BOOST_AUTO_TEST_CASE( subtract_3 )
{
    Number a(946);
    Number b(-9846);
    a -= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(946+9846));
}

BOOST_AUTO_TEST_CASE( subtract_4 )
{
    Number a(-946);
    Number b(9846);
    a -= b;
    BOOST_CHECK_EQUAL(a.to_string(),std::to_string(-946-9846));
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

    BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE( check_if_numbers_equal_false )
{
    Number a(68178);
    Number c(178);

    BOOST_CHECK(!(a == c));
}

BOOST_AUTO_TEST_CASE( check_abs_greater_than_true )
{
    Number a(12345);
    Number b(1234);

    BOOST_CHECK(a > b);
}

BOOST_AUTO_TEST_CASE( check_abs_greater_than_false )
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
