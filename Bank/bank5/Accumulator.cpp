//
// Created by cakeal on 2022/9/19.
//

#include "Accumulator.h"
#include <iostream>
using namespace std;

Accumulator::Accumulator(Date date, double value): lastDate(date), value(value), sum(0){}

const double Accumulator::getSum(Date date) {
    double a = sum + value * (date - this->lastDate);
    //cout << date - this->lastDate << endl ;
    //cout << endl << a << endl;
    return a;
}

void Accumulator::change(Date date, double value) {
    sum = getSum(date);
    lastDate = date;
    this->value = value;
}

void Accumulator::reset(Date date, double value) {
    lastDate = date;
    this->value = value;
    sum = 0;
}

Accumulator::~Accumulator() = default;
