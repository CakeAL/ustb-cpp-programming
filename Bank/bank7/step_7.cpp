//step7.cpp

#include "Account.h"
#include "date.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "stdexcept"
using namespace std;

struct deleter {
    template <class T> void operator () (T* p) { delete p; }
};

int main() {
    bool is_now_reading_a_file = true; // 1为正在读取文件，0为手动添加命令并且添加到文件内模式
    static bool only_show_once = false;
    Date date(2008, 11, 1); // 起始日期
    vector<Account *> accounts; // 创建账户数组，元素个数为0
    char cmd;
    fstream commands;
    commands.open("commands.txt", ios_base::in | ios_base::out);
    if(!commands.is_open()){
        // 文件打开失败
        commands.open("commands.txt",ios_base::out | ios_base::app);
        cout << "File cannot open or there is no such a command.txt. It will create a new file." << endl;
        is_now_reading_a_file = false;
    }
    do {
        if(cin.fail()) return 0;
        if(is_now_reading_a_file && commands.eof()){
            commands.clear();
            //commands << endl;
            is_now_reading_a_file = false;
        }
        if (!is_now_reading_a_file && !only_show_once) {
            cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit"
                << endl;
            only_show_once = true;
        }
//显示日期和总金额
        if(!is_now_reading_a_file){
            date.show();
            cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";
        }
        char type;
        int index, day;
        double amount, credit, rate, fee;
        string id, desc;
        Account* account;
        Date date1{}, date2{};
        if(is_now_reading_a_file) commands >> cmd;
        else {
            cin >> cmd;
            //if(cmd != 'e' && cmd != 's')
            //    commands << endl << cmd << " ";
        }
        switch (cmd) {
            case 'a'://增加账户
                if(is_now_reading_a_file)
                    commands >> type >> id;
                else {
                    try{
                        cin >> type >> id;
                        if(type == 's' || type == 'c'){
                            commands << endl << cmd << " ";
                            commands << type << " " << id << " ";
                        }
                        else throw runtime_error("Not a saving or credit account.");
                    }
                    catch (runtime_error& err) {
                        cerr << err.what() << endl;
                    }
                }
                if (type == 's') {
                    if(is_now_reading_a_file) commands >> rate;
                    else {
                        cin >> rate;
                        commands << rate;
                    }
                    account = new SavingsAccount(date, id, rate);
                }
                else {
                    if(is_now_reading_a_file) commands >> credit >> rate >> fee;
                    else {
                        cin >> credit >> rate >> fee;
                        commands << credit << " " << rate << " " << fee;
                    }
                    account = new CreditAccount(date, id, credit, rate, fee);
                }
                accounts.push_back(account);
                break;
            case 'd'://存入现金
                try{
                    if(is_now_reading_a_file){
                        commands >> index >> amount;
                        getline(commands, desc);
                    }
                    else{
                        cin >> index >> amount;
                        getline(cin, desc);
                        if(index < 0 || index >= accounts.size()){
                            throw runtime_error("The index you input is not exist.");
                        }
                        commands << endl << cmd << " ";
                        commands << index << " " << amount << " " << desc;
                    }
                    accounts[index]->deposit(date, amount, desc);
                }
                catch (runtime_error& err) {
                    cerr << err.what() << endl;
                }
                break;
            case 'w'://取出现金
                try{
                    if(is_now_reading_a_file){
                        commands >> index >> amount;
                        getline(commands, desc);
                    }
                    else{
                        cin >> index >> amount;
                        getline(cin, desc);
                        if(index < 0 || index >= accounts.size()){
                            throw runtime_error("The index you input is not exist.");
                        }
                    }
                    accounts[index]->withdraw(date, amount, desc);
                    // 如果没有错误再进行写入文件
                    if(!is_now_reading_a_file) {
                        commands << endl << cmd << " ";
                        commands << index << " " << amount << " " << desc;
                    }
                }
                catch (AccountException& err){
                    cerr << err.what() << endl;
                }
                catch (runtime_error& err) {
                    cerr << err.what() << endl;
                }
                break;
            case 's'://查询各账户信息
                for (size_t i = 0; i < accounts.size(); i++) {
                    cout << "[" << i << "] ";
                    accounts[i]->show();
                    cout << endl;
                }
                break;
            case 'c'://改变日期
                if(is_now_reading_a_file) commands >> day;
                else {
                    cin >> day;
                }
                if (day < date.getDay())
                    cerr << "You cannot specify a previous day" << endl;
                else if (day > date.getMaxDay())
                    cerr << "Invalid day" << endl;
                else {
                    date = Date(date.getYear(), date.getMonth(), day);
                    if(!is_now_reading_a_file) {
                        commands << endl << cmd << " ";
                        commands << day;
                    }
                }
                break;
            case 'n'://进入下个月
                if(!is_now_reading_a_file)
                    commands << endl << cmd << " ";
                if (date.getMonth() == 12)
                    date = Date(date.getYear() + 1, 1, 1);
                else
                    date = Date(date.getYear(), date.getMonth() + 1, 1);
                for (auto & iter : accounts)
                    iter->settle(date);
                break;
            case 'q'://查询一段时间内的账目
                try {
                    date1 = Date::read();
                    date2 = Date::read();
                    Account::query(date1, date2);
                }
                catch (DateException& err){
                    cerr << err.what() << endl;
                    if(cin.fail()) cin.clear();
                }
                break;
            default:
                cerr << "Not a right command." <<endl;
                break;
        }
    } while (cmd != 'e');
    for_each(accounts.begin(), accounts.end(), deleter());
    commands.close();
    return 0;
}