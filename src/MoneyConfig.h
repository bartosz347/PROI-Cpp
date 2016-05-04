#ifndef MONEYCONFIG_H_INCLUDED
#define MONEYCONFIG_H_INCLUDED

struct MoneyConfig {
    const std::string DECIMAL_SEPARATOR = ".";
    const std::string CURRENCY_SEPARATOR = " ";

    const int CurrencyRates[3] = {400,200,300};

};

enum class CurrencyTags { PLN,GBP,USD };

#endif // MONEYCONFIG_H_INCLUDED
