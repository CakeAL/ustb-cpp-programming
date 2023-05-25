//
// Created by cakeal on 2022/9/19.
//

#ifndef BANK3_ACCUMULATOR_H
#define BANK3_ACCUMULATOR_H
#include "date.h"

class Accumulator {
private:
    Date lastDate; //上次变更值的日子
    double value; //余额或者欠款
    double sum; //余额或欠款累加
public:
    Accumulator(Date date, double value);
    ~Accumulator();
    const double getSum(Date date);
    void change(Date date, double value);
    void reset(Date date, double value);
};


#endif //BANK3_ACCUMULATOR_H
