//
// Created by cakeal on 2022/9/19.
//
#ifndef BANK3_ACCOUNT_H
#define BANK3_ACCOUNT_H

#include "string"
#include "date.h"
#include "map"
#include "exception"
#include "cstdio"
using namespace std;

class AccountRecord;
class Account;

class Account {
protected:
    string id;
    string Log_on_User; //该账户隶属于哪个用户
    double balance;
    static double total;
    static multimap<Date, AccountRecord> recordMap;
public:
    Account(const Date& date, std::string id, std::string Log_on_User);
    virtual ~Account();
    void record(Date date, double amount, const string& desc); // 记录balance变化
    //const error(string msg);
    string getId() const;
    string getUser() const;
    double getBalance() const;
    virtual string show() const;
    virtual void deposit(Date date, double amount, string desc) = 0;
    virtual void withdraw(Date date, double amount, string desc) = 0;
    virtual void settle(Date date) = 0;
    virtual int s_or_c() = 0; //s = 0, c = 1;
    virtual double getDebt() = 0;
    static double getTotal();
    static string query(Date &day1, Date &day2, string user);
    static double iaxy_uzru(Date day1, Date day2, string user); // 查询区间内收入
    static double iaxy_viiu(Date day1, Date day2, string user); // 查询区间内支出
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

class AccountException : public exception{
private:
    Account* account;
public:
    explicit AccountException(Account *account): account(account){};
    const char *what() const noexcept override{
        string s1 = "Not enough money in this account:";
        string s2 = account->getId();
        string s3 = to_string(account->getBalance());
        static string s4 = s1+s2+"\tbalance:"+s3;
        return s4.c_str();
    }
};

#endif //BANK3_ACCOUNT_H
