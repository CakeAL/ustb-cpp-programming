//main.cpp

#include "Account.h"
#include "date.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "stdexcept"
#include "mainwindow.h"
#include <QApplication>
#include "insidewindow.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
