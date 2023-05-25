//
// Created by cakeal on 2022/9/19.
//

#include "Account.h"
#include <cmath>
#include "map"

double Account::total = 0;
multimap<Date, AccountRecord> Account::recordMap;
// 类的静态成员变量请记得初始化。

Account::Account(const Date& date, std::string id) : id(id), balance(0){
}

Account::~Account() = default;

void Account::record(Date date, double amount, const std::string& desc) {
    amount = floor(amount * 100 + 0.5) / 100; //保留小数点后两位
    balance += amount;
    total += amount;
    cout << date << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
    recordMap.insert(make_pair(date, AccountRecord(date,this,amount,balance,desc)));
}

std::string Account::getId() const{
    return this->id;
}

double Account::getBalance() const{
    return this->balance;
}

double Account::getTotal() {
    return total;
}

void Account::show() const {
    cout << id << "\tBalance: " << balance;
}

void Account::query(Date &day1, Date &day2) {
    for(auto & it : recordMap){
        if(day1 < it.first && it.first <day2)
            cout << it.second.date << "\t" << it.second.account->getId() << "\t" << it.second.amount << "\t"
            << it.second.balance << "\t" << it.second.desc << endl;
    }
}

AccountRecord::AccountRecord(const Date& date, const Account *account, double amount, double balance, std::string desc)
        :date(date), account(account), amount(amount), balance(balance), desc(desc){}
