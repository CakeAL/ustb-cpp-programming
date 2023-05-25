//
// Created by cakeal on 2022/9/19.
//

#include "Account.h"
#include <cmath>
#include "map"

double Account::total = 0;
multimap<Date, AccountRecord> Account::recordMap;
// 类的静态成员变量请记得初始化。

Account::Account(const Date& date, std::string Log_on_User, std::string id ) : id(id), Log_on_User(Log_on_User), balance(0){
}

Account::~Account() = default;

void Account::record(Date date, double amount, const std::string& desc) {
    amount = floor(amount * 100 + 0.5) / 100; //保留小数点后两位
    balance += amount;
    total += amount;
    cout << date << "\t"<< Log_on_User << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
    recordMap.insert(make_pair(date, AccountRecord(date,this,amount,balance,desc)));
}

std::string Account::getId() const{
    return this->id;
}

std::string Account::getUser() const{
    return this->Log_on_User;
}

double Account::getBalance() const{
    return this->balance;
}

double Account::getTotal() {
    return total;
}

std::string Account::show() const {
    //cout << id << "\tBalance: " << balance;
    return id + "\tBalance: " + std::to_string(balance);
}

string Account::query(Date &day1, Date &day2, string user) {
    string temp = "";
    for(auto & it : recordMap){
        if(day1 < it.first && it.first < day2 && it.second.account->getUser() == user){
            //cout << it.first;
            //cout << it.second;
            cout << it.first << "\t" << it.second.account->getId() << "\t" << it.second.amount << "\t"
            << it.second.balance << "\t" << it.second.desc << endl;
            temp += to_string(it.first.getYear()) + "-" + to_string(it.first.getMonth()) + "-" +
                to_string(it.first.getDay()) + "\t" + it.second.account->getId() + "\t" + to_string(it.second.amount) + "\t" +
                to_string(it.second.balance) + "\t" + it.second.desc + "\n";
        }
    }
    return temp;
}

double Account::iaxy_uzru(Date day1, Date day2, string user){
    double uzru = 0;
    for(auto & it : recordMap){
        if(day1 < it.first && it.first < day2 && it.second.account->getUser() == user){
            if(it.second.amount > 0) uzru += it.second.amount;
        }
    }
    return uzru;
}

double Account::iaxy_viiu(Date day1, Date day2, string user){
    double viiu = 0;
    for(auto & it : recordMap){
        if(day1 < it.first && it.first < day2 && it.second.account->getUser() == user){
            if(it.second.amount < 0) viiu += it.second.amount;
        }
    }
    return -viiu;
}

AccountRecord::AccountRecord(const Date& date, const Account *account, double amount, double balance, std::string desc)
        :date(date), account(account), amount(amount), balance(balance), desc(desc){}
