//
// Created by cakeal on 2022/9/19.
//

#ifndef BANK3_CREDITACCOUNT_H
#define BANK3_CREDITACCOUNT_H
#include "string"
#include "Account.h"
#include "Accumulator.h"

class CreditAccount : public Account{
private:
    Accumulator acc;
    double credit;
    double rate;
    double fee;
public:
    CreditAccount(Date date, std::string id, double credit, double rate, double fee);
    ~CreditAccount() override;
    double getDebt() const;
    double getCredit() const;
    double getRate() const;
    double getFee() const;
    double getAvailableCredit() const;
    void deposit(Date date, double amount, std::string desc) override;
    void withdraw(Date date, double amount, std::string desc) override;
    void settle(Date date) override;
    void show() const override;
};


#endif //BANK3_CREDITACCOUNT_H
