//
// Created by cakeal on 2022/9/19.
//

#include "CreditAccount.h"
#include "iostream"
using namespace std;

CreditAccount::CreditAccount(Date date, std::string id, double credit, double rate, double fee):
    Account(date, id), acc(date, 0), credit(credit), rate(rate), fee(fee) {
    cout << date << "\t#" << id << " created" << endl;
}

double CreditAccount::getRate() const{
    return this->rate;
}

double CreditAccount::getCredit() const{
    return this->credit;
}

double CreditAccount::getFee() const {
    return this->fee;
}

double CreditAccount::getAvailableCredit() const {
    if(balance > 0) return credit;
    else return credit + balance;
}

void CreditAccount::deposit(Date date, double amount, std::string desc) {
    record(date, amount, desc);
    acc.change(date, getDebt());
}

void CreditAccount::withdraw(Date date, double amount, std::string desc) {
    if(abs(amount) + abs(getBalance()) > credit){
        throw AccountException(this);
    }
    else {
        record(date, -amount, desc);
        acc.change(date, getDebt());
    }
}

void CreditAccount::settle(Date date) {
    double interest = acc.getSum(date) * rate;
    //cout << interest << endl;
    if(interest != 0){
        record(date, interest, "interest");
    }
    if(date.getMonth() == 1){
        record(date, -fee, "annual fee");
    }
    acc.reset(date, getDebt());
}

double CreditAccount::getDebt() const {
    //cout << balance << endl;
    if(balance < 0) return balance;
    else return 0;
}

void CreditAccount::show() const {
    Account::show();
    cout << "\t" << "Available credit: " << getAvailableCredit();
}

CreditAccount::~CreditAccount() = default;;