//
// Created by cakeal on 2022/9/19.
//

#include "SavingsAccount.h"
#include "Accumulator.h"
#include "iostream"
using namespace std;

SavingsAccount::SavingsAccount(Date date, std::string Log_on_User, std::string id, double rate) : Account(date, Log_on_User, id), acc(date, 0), rate(rate) {
    cout << date << "\t" << Log_on_User << "\t#" << id << " created" << endl;
}

void SavingsAccount::deposit(Date date, double amount, std::string desc) {
    record(date, amount, desc);
    acc.change(date, getBalance());
}

void SavingsAccount::withdraw(Date date, double amount, std::string desc) {
    if(amount <= getBalance()) {
        record(date, -amount, desc);
        acc.change(date, getBalance());
    }
    else throw AccountException(this);
}

double SavingsAccount::getRate() const{
    return this->rate;
}

void SavingsAccount::settle(Date date) {
    if(date.getMonth() != 1) return;
    double a = acc.getSum(date);
    int days = (date - Date(date.getYear() - 1, 1, 1)) + 1;
    double interest = a * rate / days;
    //cout << days << endl;
    //cout << a << endl;
    // cout << interest << endl;
    record(date, interest, "interest");
    acc.change(date, interest);
    acc.reset(date, getBalance());
}

