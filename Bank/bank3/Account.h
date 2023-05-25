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
    void show() const;
    static double getTotal();
};


#endif //BANK3_ACCOUNT_H
