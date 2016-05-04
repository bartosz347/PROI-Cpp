#include <boost/test/unit_test.hpp>

#include "Money.h"
#include <iostream>

/*
VALUES *loaded* from external source
    #define CURRENCIES PLN,GBP,USD
    #define CURRENCIES_STRING "PLN","GBP","USD"
    #define CURRENCIES_RATES 400,200,300
    #define CURRENCIES_NO 3



*/

#define PLN_RATE 400
#define GBP_RATE 200



BOOST_AUTO_TEST_SUITE(MoneyTests)


BOOST_AUTO_TEST_CASE( constructor_long_int )
{
    Money<currencyTag::PLN> m {};
    BOOST_CHECK_EQUAL( m.getStringName(), "PLN");
    BOOST_CHECK_EQUAL( m.getCentsValue(), 0);
    BOOST_CHECK_EQUAL( m.getMainValue(), Number{0});
    BOOST_CHECK_EQUAL( m.rateInEuro, PLN_RATE);
}

BOOST_AUTO_TEST_CASE( constructor_number )
{
    Money<currencyTag::PLN> m{Number{1519}};
    BOOST_CHECK_EQUAL( m.getStringName(), "PLN");
    BOOST_CHECK_EQUAL( m.getMainValue(), 15);
    BOOST_CHECK_EQUAL( m.getCentsValue(), 19);
    BOOST_CHECK_EQUAL( m.rateInEuro, PLN_RATE);
}

BOOST_AUTO_TEST_CASE( constructor_string )
{
    Money<currencyTag::PLN> m{"111222333444555666"};
    BOOST_CHECK_EQUAL( m.getStringName(), "PLN");
    BOOST_CHECK_EQUAL( m.getMainValue(), Number{"1112223334445556"});
    BOOST_CHECK_EQUAL( m.getCentsValue(), 66);
    BOOST_CHECK_EQUAL( m.rateInEuro, PLN_RATE);
}


BOOST_AUTO_TEST_CASE( get_as_string )
{
    Money<currencyTag::PLN> m{1234};
    BOOST_CHECK_EQUAL(m.toString(), "PLN 12.34");
}

// *
BOOST_AUTO_TEST_CASE( get_multiplied )
{
    Money<currencyTag::PLN> m (10);
    BOOST_CHECK_EQUAL((m*10).getRawValue(),10*10);
}

// *=
BOOST_AUTO_TEST_CASE( multiply )
{
    Money<currencyTag::PLN> c (10);
    c *= 10;
    BOOST_CHECK_EQUAL(c.getRawValue(), 10*10);
}

// +=
BOOST_AUTO_TEST_CASE( add_same_currency )
{
    Money<currencyTag::PLN> c1 (1234);
    Money<currencyTag::PLN> c2 (567);
    c1+=c2;
    BOOST_CHECK_EQUAL(c1.getRawValue(), 1234 + 567);
}

// +=
BOOST_AUTO_TEST_CASE( add_different_currency )
{
    Money<currencyTag::PLN> c1 (123400);
    Money<currencyTag::GBP> c2 (56700);
    c1 += c2;
    BOOST_CHECK_EQUAL(c1.getRawValue(), 123400 + (56700/GBP_RATE)*PLN_RATE);
}

// +
BOOST_AUTO_TEST_CASE( get_sum_same_currency )
{
    Money<currencyTag::PLN> c1 (1234);
    Money<currencyTag::PLN> c2 (567);
    BOOST_CHECK_EQUAL((c1+c2).getRawValue(), 1234 + 567);
}

// +
BOOST_AUTO_TEST_CASE( get_sum_different_currency )
{
    Money<currencyTag::PLN> c1 (123400);
    Money<currencyTag::GBP> c2 (56700);
    BOOST_CHECK_EQUAL((c1+c2).getRawValue(), 123400 + (56700/GBP_RATE)*PLN_RATE);
}

// -=
BOOST_AUTO_TEST_CASE( subtract_same_currency )
{
    Money<currencyTag::PLN> c1 (1234);
    Money<currencyTag::PLN> c2 (567);
    c1 -= c2;
    BOOST_CHECK_EQUAL(c1.getRawValue(), 1234 - 567);
}

// -=
BOOST_AUTO_TEST_CASE( subtract_different_currency )
{
    Money<currencyTag::PLN> c1 (123400);
    Money<currencyTag::GBP> c2 (56700);
    c1 -= c2;
    BOOST_CHECK_EQUAL(c1.getRawValue(), 123400 - (56700/GBP_RATE)*PLN_RATE);
}

// -
BOOST_AUTO_TEST_CASE( get_difference_same_currency )
{
    Money<currencyTag::PLN> c1 (1234);
    Money<currencyTag::PLN> c2 (567);
    BOOST_CHECK_EQUAL((c1-c2).getRawValue(), 1234 - 567);
}

// -
BOOST_AUTO_TEST_CASE( get_difference_different_currency )
{
    Money<currencyTag::PLN> c1 (123400);
    Money<currencyTag::GBP> c2 (56700);
    BOOST_CHECK_EQUAL((c1-c2).getRawValue(), 123400 - (56700/GBP_RATE)*PLN_RATE);
}

// ==
BOOST_AUTO_TEST_CASE( same_currency_and_equal_value )
{
    Money<currencyTag::PLN> c1 (1234);
    Money<currencyTag::PLN> c2 (1234);
    Money<currencyTag::GBP> c3 (20);
    Money<currencyTag::PLN> c4 (244);
    BOOST_CHECK_EQUAL(c1 == c2 && !(c1 == c3) && !(c1 == c4), true); //TODO split
}

// =
BOOST_AUTO_TEST_CASE( assign_test )
{
    Money<currencyTag::PLN> c1 (123400);
    Money<currencyTag::PLN> c2 (647952);

    Money<currencyTag::GBP> c3 (56700);
    // We only allow assignment within same currency!
    // c1 = c3 //error
    c1 = c2;
    BOOST_CHECK_EQUAL( c1 == c2 && c1.getRawValue() == c2.getRawValue() && c1.rateInEuro == c2.rateInEuro, 1);
}

BOOST_AUTO_TEST_CASE( conversion_test )
{
    Money<currencyTag::PLN> c1 {1234};
    Money<currencyTag::GBP> c2 {0};
    c2 = (Money<currencyTag::GBP>) c1;
    BOOST_CHECK_EQUAL( c2.getRawValue(), (1234/PLN_RATE)*GBP_RATE);
}

BOOST_AUTO_TEST_SUITE_END()
