#include <iostream>
#include <cmath>
#include <locale>
#include <string> 
#include <stdexcept>
#include "CurrencyPairs.h"
#include "User.h"

void startProgram();

class UIShell {
private:
    User user;

    void entranceWords() {
        std::cout << "Здравствуйте! Вы вошли в систему обмена валют.\n";
        showBalance();
        std::cout << "Если Вы хотите обменять, к примеру, 10 USD на EUR, напишите в консоль: \n" << "usd/eur\n" << "10\n" 
            << "\nНиже доступно меню, по которому вы сможете выбрать команду:\n" 
            << "makeExchange\n" << "showBalance\n" << "showExchangeRate\n" << "quitProgram\n\n";
    }
    
    void selectCommand() {
        std::string command;
        std::cout << "Введите название команды:\n";
        while (true) {
            std::cin >> command;
            if (!command.compare("makeExchange")) {
                makeExchange();
            } else if (!command.compare("showBalance")) {
                showBalance();
            } else if (!command.compare("showExchangeRate")) {
                showExchangeRate();
            } else if (!command.compare("quitProgram")) {
                break;
            } else {
                std::cout << "Вы ввели некорректное название команды.\n";
            }
        }
        quitProgram();
    }

    void makeExchange() {
        std::string pair;
        std::string amount;
        std::cout << "Введите названия валют, которые Вы хотите обменять: ";
        std::cin >> pair;
        std::cout << "Введите сумму для обмена: ";
        std::cin >> amount;
        std::cout << std::endl;

        try {
            if (atof(amount.c_str()) / pow (10, amount.size() - 1) < 1) {
                throw std::invalid_argument("Вы ввели некорректное значение суммы для обмена.\n");
            }
            user.selectPairToExchange(pair, atof(amount.c_str()));
            std::cout << "Обмен выполнен удачно.\n";
        } catch (std::invalid_argument& ex) {
            std::cout << ex.what();
        } 
    }

    void showExchangeRate() const {
        std::cout << "Текущий курс валют:\n"
            << "rub/usd = 1 : " << floor(rub_usd.getExchangeRation() * 100) / 100 << std::endl
            << "rub/eur = 1 : " << floor(rub_eur.getExchangeRation() * 100) / 100 << std::endl
            << "usd/eur = 1 : " << floor(usd_eur.getExchangeRation() * 100) / 100<< std::endl
            << "usd/usdt = 1: " << floor(usd_usdt.getExchangeRation() * 100) / 100<< std::endl
            << "usd/btc = 1 : " << floor(usd_btc.getExchangeRation() * 100) / 100<< std::endl;
    }

    void showBalance() const {
        user.printBalance();
    }

    void quitProgram() {
        std::cout << "Чтобы подтвердить выход из программы, напишите yes, в противном случае - любое другое слово.\n";
        std::string confirmation;
        std::cin >> confirmation;
        if (confirmation.compare("yes")) {
            selectCommand();
        }
        std::cout << "Будем рады видеть Вас снова!\n";
    }

public:
    void startUI() {
        entranceWords();
        selectCommand();
    }
};

void startProgram() {
    UIShell ui;
    ui.startUI();
}