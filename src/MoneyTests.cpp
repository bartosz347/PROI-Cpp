#include <boost/test/unit_test.hpp>

#include "Money.h"
#include <iostream>


BOOST_AUTO_TEST_SUITE(MoneyTests)


BOOST_AUTO_TEST_CASE( constructor_default )
{
    Money c ("PLN", 431);
    BOOST_CHECK_EQUAL( c.name, "PLN");
    BOOST_CHECK_EQUAL( c.getCentsValue(), 0);
    BOOST_CHECK_EQUAL( c.getMainValue(), 0);
    BOOST_CHECK_EQUAL( c.rateInEuro, 431);
}

BOOST_AUTO_TEST_CASE( constructor_legacy )
{
    Money c ("PLN", 4.3099, 1519);
    BOOST_CHECK_EQUAL( c.name.compare("PLN"),0);
    BOOST_CHECK_EQUAL( c.getMainValue(), 15);
    BOOST_CHECK_EQUAL( c.getCentsValue(), 19);
    BOOST_CHECK_EQUAL( c.rateInEuro, 431);
}

BOOST_AUTO_TEST_CASE( get_formatted_value )
{
    Money c ("PLN", 1, 1234);
    BOOST_CHECK_EQUAL(c.getFormattedValue(), "PLN 12.34");
}

// *
BOOST_AUTO_TEST_CASE( get_multiplied )
{
    Money c ("PLN", 1, 10);
    BOOST_CHECK_EQUAL((c*10).getRawValue(),10*10);
}

// *=
BOOST_AUTO_TEST_CASE( multiply )
{
    Money c ("PLN", 1, 10);
    c *= 10;
    BOOST_CHECK_EQUAL(c.getRawValue(), 10*10);
}

// +=
BOOST_AUTO_TEST_CASE( add_same_currency )
{
    Money c1 ("PLN", 431, 1234);
    Money c2 ("PLN", 431, 567);
    c1+=c2;
    BOOST_CHECK_EQUAL(c1.getRawValue(), 1234 + 567);
}

// +=
BOOST_AUTO_TEST_CASE( add_different_currency )
{
    Money c1 ("PLN", 4, 123400);
    Money c2 ("GBP", 2, 56700);
    c1 += c2;
    BOOST_CHECK_EQUAL(c1.getRawValue(), 123400 + (56700/2)*4);
}

// +
BOOST_AUTO_TEST_CASE( get_sum_same_currency )
{
    Money c1 ("PLN", 431, 1234);
    Money c2 ("PLN", 431, 567);
    BOOST_CHECK_EQUAL((c1+c2).getRawValue(), 1234 + 567);
}

// +
BOOST_AUTO_TEST_CASE( get_sum_different_currency )
{
    Money c1 ("PLN", 4, 123400);
    Money c2 ("GBP", 2, 56700);
    BOOST_CHECK_EQUAL((c1+c2).getRawValue(), 123400 + (56700/2)*4);
}

// ==
BOOST_AUTO_TEST_CASE( same_currency_and_equal_value )
{
    Money c1 ("PLN", 1, 1234);
    Money c2 ("PLN", 1, 1234);
    Money c3 ("GBP", 1, 20);
    Money c4 ("PLN", 1, 244);
    BOOST_CHECK_EQUAL(c1 == c2 && !(c1 == c3) && !(c1 == c4), true);
}


// =
BOOST_AUTO_TEST_CASE( assign_test )
{
    Money c1 ("PLN", 4, 123400);
    Money c2 ("GBP", 2, 56700);
    c1 = c2;
    BOOST_CHECK_EQUAL( c1 == c2 && c1.getRawValue() == c2.getRawValue() && c1.rateInEuro == c2.rateInEuro, 1);
}

BOOST_AUTO_TEST_SUITE_END()
