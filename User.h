#pragma once

#include <stdexcept>
#include <iostream>
#include <string> 
#include "CurrencyPairs.h"

// создаем 5 глобальных объектов для обмена валют. В дальнейшем при каждом обмене их статус будет меняться до 5%
CurrencyPair rub_usd(90); 
CurrencyPair rub_eur(100);
CurrencyPair usd_eur(1.1);
CurrencyPair usd_usdt(1.3);
CurrencyPair usd_btc(1000);

class User {
private:
    double rubles = 10000.0;
    double usd = 1000.0;
    double eur = 1000.0;
    double usdt = 1000.0;
    double btc = 1.5;

    void makeExchange(CurrencyPair& pair, double& first, double& second, double amount, int currencyToGive) {
        if (currencyToGive == 0) {
            if (first < amount) {
                throw std::invalid_argument("Недостаточно средств на счету.");
            }
            first -= amount;
            second += 1.0 / pair.getExchangeRation() * amount;
        } else {
            if (second < amount) {
                throw std::invalid_argument("Недостаточно средств на счету.\n");
            }
            second -= amount;
            first += pair.getExchangeRation() * amount;
        }

        rub_usd.changeExchangeRate();
        rub_eur.changeExchangeRate();
        usd_eur.changeExchangeRate();
        usd_usdt.changeExchangeRate();
        usd_btc.changeExchangeRate();
    }

public:
    void selectPairToExchange(std::string pair, double amount) {
        if (!pair.compare("rub/usd")) {
            makeExchange(rub_usd, rubles, usd, amount, 0);
        } else if (!pair.compare("usd/rub")) {
            makeExchange(rub_usd, rubles, usd, amount, 1);
        } else if (!pair.compare("rub/eur")) {
            makeExchange(rub_eur, rubles, eur, amount, 0);
        } else if (!pair.compare("eur/rub")) {
            makeExchange(rub_eur, rubles, eur, amount, 1);
        } else if (!pair.compare("usd/eur")) {
            makeExchange(usd_eur, usd, eur, amount, 0);
        } else if (!pair.compare("eur/usd")) {
            makeExchange(usd_eur, usd, eur, amount, 1);
        } else if (!pair.compare("usd/usdt")) {
            makeExchange(usd_usdt, usd, usdt, amount, 0);
        } else if (!pair.compare("usdt/usd")) {
            makeExchange(usd_usdt, usd, usdt, amount, 1);
        } else if (!pair.compare("usd/btc")) {
            makeExchange(usd_btc, usd, btc, amount, 0);
        } else if (!pair.compare("btc/usd")) {
            makeExchange(usd_btc, usd, btc, amount, 1);
        } else {
            throw std::invalid_argument("Вы ввели некорректные названия валют.\n");
        }
    }    

    void printBalance() const {
        std::cout << "Ваш текущий баланс:\n" 
            << "руб: " << floor(rubles * 100) / 100 << std::endl 
            << "usd: " << floor(usd * 100) / 100 << std::endl 
            << "eur: " << floor(eur * 100) / 100 << std::endl 
            << "usdt: " << floor(usdt * 100) / 100 << std::endl 
            << "btc: " << floor(btc * 100) / 100 << std::endl << std::endl;
    }
};
