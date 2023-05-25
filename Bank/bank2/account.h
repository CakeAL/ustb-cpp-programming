#ifndef __ACCOUNT__
#define __ACCOUNT__

#include <string>
#include "date.h"
using namespace std;

class SavingsAccount;

class SavingsAccount
{
private:
    /* data */
    string _id;//账户
    double _balance;//余额
    double _rate;//年利率
    int _lastDate;
    double _accumulation;//积累
    static double total; // 所有用户总金额
public:
    SavingsAccount(Date date, string id, double rate);
    ~SavingsAccount();
    void record(int date, double amount);
    double accumulate(int date);
    int getId();
    double getBalance();
    double getRate();
    void show();
    void deposit(Date date, double amount, const char *things);
    void withdraw(Date date, double amount, const char *things);
    void settle(Date date);
    static double getTotal();

};



#endif