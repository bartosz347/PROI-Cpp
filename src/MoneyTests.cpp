#include <boost/test/unit_test.hpp>

#include "Money.h"

static const int PLN_RATE = 400;
static const int GBP_RATE = 200;

BOOST_AUTO_TEST_SUITE(MoneyTests)


BOOST_AUTO_TEST_CASE( constructor_empty )
{
    Money<CurrencyTag::PLN> m{};
    BOOST_CHECK_EQUAL( m.getStringName(), "PLN");
    BOOST_CHECK_EQUAL( m.getCentsValue(), 0);
    BOOST_CHECK_EQUAL( m.getMainValue(), Number{0});
    BOOST_CHECK_EQUAL( m.getEuroRate(), PLN_RATE);
}

BOOST_AUTO_TEST_CASE( constructor_number )
{
    Money<CurrencyTag::PLN> m{Number{1519}};
    BOOST_CHECK_EQUAL( m.getStringName(), "PLN");
    BOOST_CHECK_EQUAL( m.getMainValue(), 15);
    BOOST_CHECK_EQUAL( m.getCentsValue(), 19);
}

BOOST_AUTO_TEST_CASE( constructor_string )
{
    std::string n{"111222333444555666"};
    Money<CurrencyTag::PLN> m(n);
    BOOST_CHECK_EQUAL( m.getStringName(), "PLN");
    BOOST_CHECK_EQUAL( m.getMainValue(), Number{"1112223334445556"});
    BOOST_CHECK_EQUAL( m.getCentsValue(), 66);
}

BOOST_AUTO_TEST_CASE( get_as_string )
{
    Money<CurrencyTag::PLN> m{1234};
    BOOST_CHECK_EQUAL(m.toString(), "PLN 12.34");
}

// *
BOOST_AUTO_TEST_CASE( get_multiplied )
{
    Money<CurrencyTag::PLN> m (10);
    BOOST_CHECK_EQUAL((m*10).getValue(),10*10);
}

// *=
BOOST_AUTO_TEST_CASE( multiply )
{
    Money<CurrencyTag::PLN> c (10);
    c *= 10;
    BOOST_CHECK_EQUAL(c.getValue(), 10*10);
}

// +=
BOOST_AUTO_TEST_CASE( add_same_currency )
{
    Money<CurrencyTag::PLN> c1 (1234);
    Money<CurrencyTag::PLN> c2 (567);
    c1+=c2;
    BOOST_CHECK_EQUAL(c1.getValue(), 1234 + 567);
}

// +=
BOOST_AUTO_TEST_CASE( add_different_currency )
{
    Money<CurrencyTag::PLN> c1 (123400);
    Money<CurrencyTag::GBP> c2 (56700);
    c1 += c2;
    BOOST_CHECK_EQUAL(c1.getValue(), 123400 + (56700/GBP_RATE)*PLN_RATE);
}

// +
BOOST_AUTO_TEST_CASE( get_sum_same_currency )
{
    Money<CurrencyTag::PLN> c1 (1234);
    Money<CurrencyTag::PLN> c2 (567);
    BOOST_CHECK_EQUAL((c1+c2).getValue(), 1234 + 567);
}

// +
BOOST_AUTO_TEST_CASE( get_sum_different_currency )
{
    Money<CurrencyTag::PLN> c1 (123400);
    Money<CurrencyTag::GBP> c2 (56700);
    BOOST_CHECK_EQUAL((c1+c2).getValue(), 123400 + (56700/GBP_RATE)*PLN_RATE);
}

// -=
BOOST_AUTO_TEST_CASE( subtract_same_currency )
{
    Money<CurrencyTag::PLN> c1 (1234);
    Money<CurrencyTag::PLN> c2 (567);
    c1 -= c2;
    BOOST_CHECK_EQUAL(c1.getValue(), 1234 - 567);
}

// -=
BOOST_AUTO_TEST_CASE( subtract_different_currency )
{
    Money<CurrencyTag::PLN> c1 (123400);
    Money<CurrencyTag::GBP> c2 (56700);
    c1 -= c2;
    BOOST_CHECK_EQUAL(c1.getValue(), 123400 - (56700/GBP_RATE)*PLN_RATE);
}

// -
BOOST_AUTO_TEST_CASE( get_difference_same_currency )
{
    Money<CurrencyTag::PLN> c1 (1234);
    Money<CurrencyTag::PLN> c2 (567);
    BOOST_CHECK_EQUAL((c1-c2).getValue(), 1234 - 567);
}

// -
BOOST_AUTO_TEST_CASE( get_difference_different_currency )
{
    Money<CurrencyTag::PLN> c1 (123400);
    Money<CurrencyTag::GBP> c2 (56700);
    BOOST_CHECK_EQUAL((c1-c2).getValue(), 123400 - (56700/GBP_RATE)*PLN_RATE);
}

// ==
BOOST_AUTO_TEST_CASE( same_currency_and_equal_value_true )
{
    Money<CurrencyTag::PLN> c1 (1234);
    Money<CurrencyTag::PLN> c2 (1234);
    BOOST_CHECK(c1 == c2);
}

// ==
BOOST_AUTO_TEST_CASE( same_currency_and_equal_value_false_1 )
{
    Money<CurrencyTag::PLN> c1 (1234);
    Money<CurrencyTag::GBP> c2 (1234);
    BOOST_CHECK(!(c1 == c2));
}

// ==
BOOST_AUTO_TEST_CASE( same_currency_and_equal_value_false_2 )
{
    Money<CurrencyTag::PLN> c1 (1234);
    Money<CurrencyTag::PLN> c2 (20);
    BOOST_CHECK(!(c1 == c2));
}

// =
BOOST_AUTO_TEST_CASE( assign_test_values )
{
    Money<CurrencyTag::PLN> c1 (123400);
    Money<CurrencyTag::PLN> c2 (647952);

    Money<CurrencyTag::GBP> c3 (56700);
    // We only allow assignment within same currency!
    // c1 = c3 //error
    c1 = c2;
    BOOST_CHECK( c1 == c2 && c1.getValue() == c2.getValue());
}

// =
BOOST_AUTO_TEST_CASE( assign_test_equality )
{
    Money<CurrencyTag::PLN> c1 (123400);
    Money<CurrencyTag::PLN> c2 (647952);

    Money<CurrencyTag::GBP> c3 (56700);
    // We only allow assignment within same currency!
    // c1 = c3 //error
    c1 = c2;
    BOOST_CHECK( c1 == c2 );
}

// =
BOOST_AUTO_TEST_CASE( assign_test_rates )
{
    Money<CurrencyTag::PLN> c1 (123400);
    Money<CurrencyTag::PLN> c2 (647952);

    Money<CurrencyTag::GBP> c3 (56700);
    // We only allow assignment within same currency!
    // c1 = c3 //error
    c1 = c2;
    BOOST_CHECK( c1.getEuroRate() == c2.getEuroRate());
}

BOOST_AUTO_TEST_CASE( conversion_test )
{
    Money<CurrencyTag::PLN> c1 {1234};
    Money<CurrencyTag::GBP> c2 {0};
    c2 = (Money<CurrencyTag::GBP>) c1;
    BOOST_CHECK_EQUAL( c2.getValue(), (1234/PLN_RATE)*GBP_RATE);
}

BOOST_AUTO_TEST_SUITE_END()
