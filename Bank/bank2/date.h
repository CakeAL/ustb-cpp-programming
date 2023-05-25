#ifndef __Date__
#define __Date__

class Date;

class Date
{
private:
public:
    int _year, _month, _day;
    int the_days_from_the_begin; // 从1900年1月1日开始
    Date(int year, int month, int day);
    ~Date();
};

#endif