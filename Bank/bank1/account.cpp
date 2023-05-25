#include "account.h"
#include <cmath>
#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;

SavingsAccount::SavingsAccount(int date, int id, double rate)
{
    //_lastDate = date;
    this->_lastDate = date;
    this->_id = id;
    _rate = rate;
    _balance = 0; //初始金额为0
    _accumulation = 0;//初始利息积累为0
    cout << date << "\t#" << this->_id << " is created" << endl;
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

void SavingsAccount::deposit(int date, double amount){
    // 这是这一段时间内的利息
    amount = floor(amount * 100 + 0.5) / 100;
    _accumulation += ( date - _lastDate ) * _balance * _rate / 365; //计算这几天的利息
    _balance += amount; // 然后存了钱之后的钱
    _lastDate = date;
    cout << date << "\t#" << _id << "\t" << amount << "\t" << _balance << endl;
}
void SavingsAccount::withdraw(int date, double amount){
    // 这是这一段时间内的利息
    amount = floor(amount * 100 + 0.5) / 100;
    _accumulation += ( date - _lastDate ) * _balance * _rate / 365; //计算这几天的利息
    _balance -= amount; // 然后存了钱之后的钱
    _lastDate = date;
    cout << date << "\t#" << _id << "\t-" << amount << "\t" << _balance << endl;
}

void SavingsAccount::settle(int date){
    _accumulation += ( date - _lastDate ) * _balance * _rate / 365; //计算这几天的利息
    _balance += _accumulation;
    cout << date << "\t#" << _id << "\t" << fixed << setprecision(2) << _accumulation << "\t";
    cout.unsetf(ios::fixed);
    cout.precision(6);
    cout << _balance << endl;
    //printf("%d\t#%d\t%.2lf\t%.2lf\n",date,_id,_accumulation,_balance);
    _lastDate = date;
}

void SavingsAccount::show(){
    //printf("#%d\tBalance: %.2lf",_id,_balance);
    cout.precision(6);
    cout << "#" << _id << "\tBalance: " << _balance;
}

