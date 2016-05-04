#ifndef MONEYCONFIG_H_INCLUDED
#define MONEYCONFIG_H_INCLUDED

struct MoneyConfig {
    const std::string DECIMAL_SEPARATOR = ".";
    const std::string CURRENCY_SEPARATOR = " ";
    const std::string CurrencyTagNames[3] = {"PLN","GBP","USD"};
    const int CurrencyRates[3] = {400,200,300};

};

enum class CurrencyTag { PLN,GBP,USD };

#endif // MONEYCONFIG_H_INCLUDED
