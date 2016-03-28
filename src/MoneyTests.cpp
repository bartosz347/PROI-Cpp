#include <boost/test/unit_test.hpp>

#include "Money.h"
#include <iostream>


BOOST_AUTO_TEST_SUITE(MoneyTests)


BOOST_AUTO_TEST_CASE( constructor_default )
{
    Money<currencyTag::PLN> m {431,0};
    BOOST_CHECK_EQUAL( m.getStringName(), "PLN");
    BOOST_CHECK_EQUAL( m.getCentsValue(), 0);
    BOOST_CHECK_EQUAL( m.getMainValue(), 0);
    BOOST_CHECK_EQUAL( m.rateInEuro, 431);
}

BOOST_AUTO_TEST_CASE( constructor_number )
{
    Money<currencyTag::PLN> m(431, Number(1519)); // ASK difference between {args} and (args) when calling constructor
    BOOST_CHECK_EQUAL( m.getStringName(), "PLN");
    BOOST_CHECK_EQUAL( m.getMainValue(), 15);
    BOOST_CHECK_EQUAL( m.getCentsValue(), 19);
    BOOST_CHECK_EQUAL( m.rateInEuro, 431);
}

BOOST_AUTO_TEST_CASE( get_formatted_value )
{
    Money<currencyTag::PLN> m(1, 1234);
    BOOST_CHECK_EQUAL(m.getFormattedValue(), "PLN 12.34");
}

// *
BOOST_AUTO_TEST_CASE( get_multiplied )
{
    Money<currencyTag::PLN> m (1, 10);
    BOOST_CHECK_EQUAL((m*10).getRawValue(),10*10);
}

// *=
BOOST_AUTO_TEST_CASE( multiply )
{
    Money<currencyTag::PLN> c (1, 10);
    c *= 10;
    BOOST_CHECK_EQUAL(c.getRawValue(), 10*10);
}

// +=
BOOST_AUTO_TEST_CASE( add_same_currency )
{
    Money<currencyTag::PLN> c1 (431, 1234);
    Money<currencyTag::PLN> c2 (431, 567);
    c1+=c2;
    BOOST_CHECK_EQUAL(c1.getRawValue(), 1234 + 567);
}

// +=
BOOST_AUTO_TEST_CASE( add_different_currency )
{
    Money<currencyTag::PLN> c1 (4, 123400);
    Money<currencyTag::GBP> c2 (2, 56700);
    c1 += c2;
    BOOST_CHECK_EQUAL(c1.getRawValue(), 123400 + (56700/2)*4);
}

// +
BOOST_AUTO_TEST_CASE( get_sum_same_currency )
{
    Money<currencyTag::PLN> c1 ( 431, 1234);
    Money<currencyTag::PLN> c2 ( 431, 567);
    BOOST_CHECK_EQUAL((c1+c2).getRawValue(), 1234 + 567);
}

// +
BOOST_AUTO_TEST_CASE( get_sum_different_currency )
{
    Money<currencyTag::PLN> c1 (4, 123400);
    Money<currencyTag::GBP> c2 (2, 56700);
    BOOST_CHECK_EQUAL((c1+c2).getRawValue(), 123400 + (56700/2)*4);
}

// ==
BOOST_AUTO_TEST_CASE( same_currency_and_equal_value )
{
    Money<currencyTag::PLN> c1 (1, 1234);
    Money<currencyTag::PLN> c2 (1, 1234);
    Money<currencyTag::GBP> c3 (1, 20);
    Money<currencyTag::PLN> c4 (1, 244);
    BOOST_CHECK_EQUAL(c1 == c2 && !(c1 == c3) && !(c1 == c4), true);
}


// =
BOOST_AUTO_TEST_CASE( assign_test )
{
    Money<currencyTag::PLN> c1 (4, 123400);
    Money<currencyTag::PLN> c2 (4, 647952);

    Money<currencyTag::GBP> c3 (2, 56700);
    // We only allow assignment within same currency!
    // c1 = c3 //error
    c1 = c2;
    BOOST_CHECK_EQUAL( c1 == c2 && c1.getRawValue() == c2.getRawValue() && c1.rateInEuro == c2.rateInEuro, 1);
}

BOOST_AUTO_TEST_SUITE_END()
