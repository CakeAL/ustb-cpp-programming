#include "account.h"
#include "date.h"
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

double SavingsAccount::total = 0;

SavingsAccount::SavingsAccount(Date date, string id, double rate)
{
    _lastDate = date.the_days_from_the_begin;
    _id = id;
    _rate = rate;
    _balance = 0; //初始金额为0
    _accumulation = 0;//初始利息积累为0
    cout << date._year << "-" << date._month << "-" << date._day << "\t#" << _id << " created" << endl;
}

SavingsAccount::~SavingsAccount()
{
}

void SavingsAccount::record(int date, double amount){
    // //_accumulation = accumulate(date);
    // _lastDate = date;
    // amount = floor(amount * 100 + 0.5) / 100;
    // _balance += amount;
    // // total
    // cout << date << "\t#" << _id << "\t" << amount << "\t" << _balance << endl;

}

void SavingsAccount::deposit(Date date, double amount, const char* things){
    // 这是这一段时间内的利息
    amount = floor(amount * 100 + 0.5) / 100;
    _accumulation += ( date.the_days_from_the_begin - _lastDate ) * _balance * _rate / 366; //计算这几天的利息
    _accumulation = floor(_accumulation * 100 + 0.5) / 100;
    _balance += amount; // 然后存了钱之后的钱
    _lastDate = date.the_days_from_the_begin;
    cout << date._year << "-" << date._month << "-" << date._day << "\t#" << _id << "\t" << amount << "\t" << _balance << "\t" << things <<endl;
}
void SavingsAccount::withdraw(Date date, double amount, const char* things){
    // 这是这一段时间内的利息
    amount = floor(amount * 100 + 0.5) / 100;
    _accumulation += ( date.the_days_from_the_begin - _lastDate ) * _balance * _rate / 366; //计算这几天的利息
    _accumulation = floor(_accumulation * 100 + 0.5) / 100;
    _balance -= amount; // 然后存了钱之后的钱
    _lastDate = date.the_days_from_the_begin;
    cout << date._year << "-" << date._month << "-" << date._day << "\t#" << _id << "\t-" << amount << "\t" << _balance << "\t" << things <<endl;
}

void SavingsAccount::settle(Date date){
    _accumulation += ( date.the_days_from_the_begin - _lastDate ) * _balance * _rate / 366; //计算这几天的利息
    //printf("%lf\n",_accumulation);
    _accumulation = floor(_accumulation * 100 + 0.5) / 100;
    //printf("%lf\n",_accumulation);
    _balance += _accumulation;
    cout << date._year << "-" << date._month << "-" << date._day << "\t#" << _id << "\t" <<_accumulation << "\t";
    cout.unsetf(ios::fixed);
    cout.precision(6);
    cout << _balance << "\tinterest" <<endl;
    _lastDate = date.the_days_from_the_begin;
    total += _balance; // 计算total
}

void SavingsAccount::show(){
    cout.precision(6);
    cout << _id << "\tBalance: " << _balance;
}

double SavingsAccount::getTotal() {
    return total;
}

