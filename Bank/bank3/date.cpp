#include "date.h"

Date::Date(int year, int month, int day):year(year), month(month), day(day)
{
    totalDays = distance();
}

Date::~Date()
= default;

//用于转换年月日为为1900年1月1日距今多少天
int Date::distance() const
{
    int the_days_form_the_begin = 0;
    int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    the_days_form_the_begin += (year - 1900) * 365 + (year - 1900) / 4 - (year - 1900) / 100 + (year - 1900 + 300) / 400;
    for(int i = 1; i < month; i++){
        the_days_form_the_begin += days_in_month[i];
    }
    if(month > 2) the_days_form_the_begin += (int)((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
    the_days_form_the_begin += day - 1;
    if(month == 1 && day == 1) the_days_form_the_begin++;
    // cout<<the_days_form_the_begin<<endl;
    return the_days_form_the_begin;
}

int Date::operator - (const Date &d) const {
    return this->totalDays - d.totalDays;
}

int Date::getYear() const {
    return this->year;
}

int Date::getMonth() const{
    return this->month;
}

int Date::getDay() const{
    return this->day;
}

bool Date::isLeapYear() const{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int Date::getTotalDays() const{
    return this->totalDays;
}

ostream &operator<<(ostream &out, Date &date) {
    return out << date.year << "-" << date.month << "-" << date.day;
}


