#include "date.h"
using namespace std;

int TransTheDays(int year, int month, int day);

Date::Date(int year, int month, int day)
{
    _year = year;
    _month = month;
    _day = day;
    the_days_from_the_begin = TransTheDays(year, month, day);
}

Date::~Date()
{
}

//用于转换年月日为为1900年1月1日距今多少天
int TransTheDays(int year, int month, int day)
{
    int the_days_form_the_begin = 0; //定义一个量，表示最后算出来的天数，距离1900年1月1日多少天
    //每个月的天数（不是闰年）
    int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool is_a_leap_year = false; //是否是闰年
    //判断是否是闰年
    if (year % 400 == 0) is_a_leap_year = true;
    else if (year % 100 == 0) is_a_leap_year = false;
    else if (year % 4 == 0) is_a_leap_year = true;
    //通过这个计算，算出当年1月1日到1900年1月1日多少天
    the_days_form_the_begin += (year - 1900) * 365 + (year - 1900) / 4 - (year - 1900) / 100 + (year - 1900 + 300) / 400;
    for(int i = 1; i < month; i++){//按月累加进总天数
        the_days_form_the_begin += days_in_month[i];
    }
    //如果超过2月，那么加上是否是闰年的布尔值，如果是闰年就是1，不是闰年就加上0
    if(month > 2) the_days_form_the_begin += (int)is_a_leap_year;
    the_days_form_the_begin += day - 1; //当月距离第一天有几天
    if(day == 1) the_days_form_the_begin += 1;
    // cout<<the_days_form_the_begin<<endl;
    return the_days_form_the_begin;//返回最后的值
}