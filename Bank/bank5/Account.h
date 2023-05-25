//
// Created by cakeal on 2022/9/19.
//
#ifndef BANK3_ACCOUNT_H
#define BANK3_ACCOUNT_H

#include "string"
#include "date.h"
#include "map"
using namespace std;

class AccountRecord;
class Account;

class Account {
protected:
    string id;
    double balance;
    static double total;
    static multimap<Date, AccountRecord> recordMap;
public:
    Account(const Date& date, std::string id);
    virtual ~Account();
    void record(Date date, double amount, const string& desc); // 记录balance变化
    //const error(string msg);
    string getId() const;
    double getBalance() const;
    virtual void show() const;
    virtual void deposit(Date date, double amount, string desc) = 0;
    virtual void withdraw(Date date, double amount, string desc) = 0;
    virtual void settle(Date date) = 0;
    static double getTotal();
    static void query (Date &day1, Date &day2);
};

class AccountRecord { // 账目记录
public:
    Date date;              //日期
    const Account *account; //账户
    double amount;          //金额
    double balance;         //余额
    string desc;            //描述
    AccountRecord(const Date& date, const Account *account, double amount, double balance, string desc);

};

#endif //BANK3_ACCOUNT_H
