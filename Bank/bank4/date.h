#ifndef __Date__
#define __Date__

#include "iostream"
using namespace std;
class Date;

class Date
{
private:
    int year, month, day;
    int totalDays; // 从1900年1月1日开始
public:
    Date(int year, int month, int day);
    ~Date();
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    bool isLeapYear() const;
    int getTotalDays() const;
    int getMaxDay() const;
    int distance() const; //获得从1900年1月1日距今多少天
    void show() const;
    int operator - (const Date &d) const; //重载运算符，前面的减去后面的
    friend ostream & operator<<(ostream &out, Date &date); //cout << date
};

#endif