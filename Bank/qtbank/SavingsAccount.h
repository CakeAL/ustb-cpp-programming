//
// Created by cakeal on 2022/9/19.
//

#ifndef BANK3_SAVINGSACCOUNT_H
#define BANK3_SAVINGSACCOUNT_H

#include <string>
#include "Account.h"
#include "Accumulator.h"

class SavingsAccount :public Account{
private:
    Accumulator acc;
    double rate;
public:
    SavingsAccount(Date date, std::string Log_on_User, std::string id, double rate);
    double getRate() const;
    void deposit(Date date, double amount, std::string desc) override;
    void withdraw(Date date, double amount, std::string desc) override;
    void settle(Date date) override;
    double getDebt() override{
        return 0;
    }
    int s_or_c() override{
        return 0;
    }
};


#endif //BANK3_SAVINGSACCOUNT_H
