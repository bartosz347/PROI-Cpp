#include <boost/test/unit_test.hpp>

#include "Currency.h"
#include "CurrencyOperators.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(CurrencyTests)

BOOST_AUTO_TEST_CASE( constructor_default )
{
    Currency c ("PLN", 431);
    BOOST_CHECK_EQUAL( c.name.compare("PLN"),0);
    BOOST_CHECK_EQUAL( c.getCentsValue(), 0);
    BOOST_CHECK_EQUAL( c.getMainValue(), 0);
}
BOOST_AUTO_TEST_CASE( constructor_ext )
{
    Currency c ("PLN", 4.3099, 1519);
    BOOST_CHECK_EQUAL( c.name.compare("PLN"),0);
    BOOST_CHECK_EQUAL( c.getMainValue(), 15);
    BOOST_CHECK_EQUAL( c.getCentsValue(), 19);
    BOOST_CHECK_EQUAL( c.rateInEuro, 431);
}

BOOST_AUTO_TEST_CASE( get_formatted_value )
{
    Currency c ("PLN", 1, 1234);
    BOOST_CHECK_EQUAL(c.getFormattedValue().compare("PLN 12.34"), 0);
}

// *
BOOST_AUTO_TEST_CASE( get_multiplied )
{
    Currency c ("PLN", 1, 10);
    BOOST_CHECK_EQUAL((c*10).getRawValue(),10*10);
}

// *=
BOOST_AUTO_TEST_CASE( multiply )
{
    Currency c ("PLN", 1, 10);
    c *= 10;
    BOOST_CHECK_EQUAL(c.getRawValue(), 10*10);
}

// +=
BOOST_AUTO_TEST_CASE( add_same_currency )
{
    Currency c1 ("PLN", 4.3099, 1234);
    Currency c2 ("PLN", 4.3099, 567);
    c1+=c2;
    BOOST_CHECK_EQUAL(c1.getRawValue(), 1234 + 567);
}

// +=
BOOST_AUTO_TEST_CASE( add_different_currency )
{
    Currency c1 ("PLN", 4.3099, 123400);
    Currency c2 ("GBP", 0.77595, 56700);
    c1 += c2;
    BOOST_CHECK_EQUAL(c1.getRawValue(), 436737);
}

// +
BOOST_AUTO_TEST_CASE( get_sum_same_currency )
{
    Currency c1 ("PLN", 4.3099, 1234);
    Currency c2 ("PLN", 4.3099, 567);
    BOOST_CHECK_EQUAL((c1+c2).getRawValue(), 1234 + 567);
}

// +
BOOST_AUTO_TEST_CASE( get_sum_different_currency )
{
    Currency c1 ("PLN", 4.3099, 123400);
    Currency c2 ("GBP", 0.77595, 56700);
    BOOST_CHECK_EQUAL((c1+c2).getRawValue(), 436737);
}

// ==
BOOST_AUTO_TEST_CASE( are_in_same_currency )
{
    Currency c1 ("PLN", 1, 1234);
    Currency c2 ("PLN", 1, 1234);
    Currency c3 ("GBP", 1, 20);
    BOOST_CHECK_EQUAL(c1 == c2 && !(c1 == c3), true);
}

// =
BOOST_AUTO_TEST_CASE( assign_test )
{
    Currency c1 ("PLN", 4.3099, 123400);
    Currency c2 ("GBP", 0.77595, 56700);
    c1 = c2;
    BOOST_CHECK_EQUAL( c1 == c2 && c1.getRawValue() == c2.getRawValue() && c1.rateInEuro == c2.rateInEuro, 1);
}


BOOST_AUTO_TEST_SUITE_END()
