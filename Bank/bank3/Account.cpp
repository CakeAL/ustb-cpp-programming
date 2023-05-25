//
// Created by cakeal on 2022/9/19.
//

#include "Account.h"
#include <cmath>
#include <string>

double Account::total = 0;

Account::Account(Date date, std::string id) : id(id){
}

Account::~Account() = default;

void Account::record(Date date, double amount, std::string desc) {
    amount = floor(amount * 100 + 0.5) / 100; //保留小数点后两位
    balance += amount;
    total += amount;
    cout << date << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
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


