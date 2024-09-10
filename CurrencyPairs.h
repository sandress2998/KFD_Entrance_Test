#pragma once

#include <random>

class CurrencyPair { // курс всегда будет firstCurrency : secondCurrency = 1 : X, где X может быть любым, а 1 фиксировано.
private:
    double exchangeRation; // = X 

    double getRandomPercent() const { // получаем случайное число от -0.05 до 0.05 (но 0 при этом возвратиться не может) 
        return (rand() % 500 + 1) / 10000.0 * (rand() % 2 ? (-1) : 1);
    }

public:
    CurrencyPair(double defaultExchangeRation): exchangeRation(defaultExchangeRation) {}   

    double getExchangeRation( ) const {
        return exchangeRation;
    }

    void changeExchangeRate() {
        exchangeRation += exchangeRation * getRandomPercent();
    }
};
