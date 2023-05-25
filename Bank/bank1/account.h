#ifndef __ACCOUNT__
#define __ACCOUNT__

class SavingsAccount;

class SavingsAccount
{
private:
    /* data */
    int _id;//账户
    double _balance;//余额
    double _rate;//年利率
    int _lastDate;
    double _accumulation;//积累
public:
    SavingsAccount(int date, int id, double rate);
    ~SavingsAccount();
    void record(int date, double amount);
    double accumulate(int date);
    int getId();
    double getBalance();
    double getRate();
    void show();
    void deposit(int date, double amount);
    void withdraw(int date, double amount);
    void settle(int date);
};


#endif