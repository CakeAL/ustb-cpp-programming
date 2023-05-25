//
// Created by cakeal on 2022/9/19.
//

#ifndef BANK3_ACCOUNT_H
#define BANK3_ACCOUNT_H

#include "string"
#include "date.h"

class Account {
protected:
    std::string id;
    double balance;
    static double total;
public:
    Account(Date date, std::string id);
    ~Account();
    void record(Date date, double amount, std::string desc); // 记录balance变化
    //const error(string msg);
    std::string getId() const;
    double getBalance() const;
    virtual void show() const;
    virtual void deposit(Date date, double amount, std::string desc) = 0;
    virtual void withdraw(Date date, double amount, std::string desc) = 0;
    virtual void settle(Date date) = 0;
    static double getTotal();
};


#endif //BANK3_ACCOUNT_H
