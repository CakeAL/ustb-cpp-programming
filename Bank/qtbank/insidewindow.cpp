#include "insidewindow.h"
#include "ui_insidewindow.h"
#include "QString"
#include "QDebug"
#include "date.h"
#include "vector"
#include "Account.h"
#include "fstream"
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include "stdexcept"
#include "iostream"
#include "QMessageBox"
using namespace std;

struct deleter {
    template <class T> void operator () (T* p) { delete p; }
};

InsideWindow *InsideWindow::iw = nullptr;

Date date(2008, 11, 1); // 起始日期
fstream commands;
vector<Account *> accounts; // 创建账户数组，元素个数为0
QString aa[5]; // 0.s or c 1.账户名 2.信用 3.利率 4.年费
QString ddww[3]; // 0.账户名编号 1.金额 2.原因
int day_change;
Date q1,q2;

InsideWindow::InsideWindow(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::InsideWindow)
{
    ui->setupUi(this);
    iw = this;
    //qDebug() << QString::fromStdString(this->MainWindow::Log_on_User);
    QString theHello = "欢迎用户 "+ QString::fromStdString(this->MainWindow::Log_on_User) +" ，请进行接下来的操作：先在对应框内输入内容，再点击按钮，在下方会显示对应结果。";
    ui->label->setText(theHello);

    //初始化只加载一次
    //static bool is_now_reading_a_file = true; // 1为正在读取文件，0为手动添加命令并且添加到文件内模式
    //    static bool only_show_once = false;
    char cmd;
    commands.open("commands.txt", ios_base::in | ios_base::out);
    if(!commands.is_open()){
     // 文件打开失败
        commands.open("commands.txt",ios_base::out | ios_base::app);
     // cout << "File cannot open or there is no such a command.txt. It will create a new file." << endl;
     //is_now_reading_a_file = false;
    }
    else {
        do{
            commands >> cmd;
            InsideWindow::backMain(cmd, true);
        }while(!commands.eof());
        commands.clear();
    }
    InsideWindow::jisrBro2();
}

InsideWindow::~InsideWindow()
{
    for_each(accounts.begin(), accounts.end(), deleter());
    commands.close();
    delete ui;
}

void InsideWindow::recvInsideWindow(){
    this->show();
}

void InsideWindow::backMain(char cmd, bool is_now_reading_a_file){
//            if (!is_now_reading_a_file && !only_show_once) {
//                cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit"
//                    << endl;
//                only_show_once = true;
//            }
    //显示日期和总金额
            if(!is_now_reading_a_file){
                date.show();
                cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";
            }
            char type;
            unsigned int index; int day;
            double amount, credit, rate, fee;
            string user, id, desc;
            Account* account;
            Date date1{}, date2{};
//            if(is_now_reading_a_file) commands >> cmd;
//            else {
//                cin >> cmd;
//                //if(cmd != 'e' && cmd != 's')
//                //    commands << endl << cmd << " ";
//            }
            switch (cmd) {
                case 'a'://增加账户
                    if(is_now_reading_a_file)
                        commands >> type >> user >> id;
                    else {
                        try{
                            //cin >> type >> user >> id;
                            type = aa[0].toStdString().c_str()[0];
                            user = MainWindow::Log_on_User;
                            id = aa[1].toStdString();

                            if(type == 's' || type == 'c'){
                                commands << endl << cmd << " ";
                                commands << type << " " << user << " " << id << " ";
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
                            //cin >> rate;
                            rate = aa[3].toDouble();
                            commands << rate;
                        }
                        account = new SavingsAccount(date, user , id, rate);
                    }
                    else {
                        if(is_now_reading_a_file) commands >> credit >> rate >> fee;
                        else {
                            //cin >> credit >> rate >> fee;
                            credit = aa[2].toDouble();
                            rate = aa[3].toDouble();
                            fee = aa[4].toDouble();
                            commands << credit << " " << rate << " " << fee;
                        }
                        account = new CreditAccount(date, user, id, credit, rate, fee);
                    }
                    if(user == MainWindow::Log_on_User) //进行用户过滤
                        iw->ui->textBrowser1->append(QString::fromStdString(user+"的"+id+"账号已创建."));
                    accounts.push_back(account);
                    break;
                case 'd'://存入现金
                    try{
                        if(is_now_reading_a_file){
                            commands >> index >> amount;
                            getline(commands, desc);
                        }
                        else{
                            //cin >> index >> amount;
                            //getline(cin, desc);
                            index = ddww[0].toUInt();
                            amount = ddww[1].toDouble();
                            desc = ddww[2].toStdString();
                            if(index < 0 || index >= accounts.size()){
                                throw runtime_error("The index you input is not exist.");
                            }
                            commands << endl << cmd << " ";
                            commands << index << " " << amount << " " << desc;
                            InsideWindow::jisrBro2();
                        }
                        accounts[index]->deposit(date, amount, desc);
                        if(accounts[index]->getUser() == MainWindow::Log_on_User) // 进行用户过滤
                            iw->ui->textBrowser1->append(QString::fromStdString(to_string(date.getYear())+"年"+to_string(date.getMonth())+"月"+to_string(date.getDay())+"日"+accounts[index]->getId()+"存了"+to_string(amount)+"元,原因："+desc));
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
                            //cin >> index >> amount;
                            //getline(cin, desc);
                            index = ddww[0].toUInt();
                            amount = ddww[1].toDouble();
                            desc = ddww[2].toStdString();
                            if(index < 0 || index >= accounts.size()){
                                throw runtime_error("The index you input is not exist.");
                            }
                            InsideWindow::jisrBro2();
                        }
                        accounts[index]->withdraw(date, amount, desc);
                        if(accounts[index]->getUser() == MainWindow::Log_on_User) // 进行用户过滤
                            iw->ui->textBrowser1->append(QString::fromStdString(to_string(date.getYear())+"年"+to_string(date.getMonth())+"月"+to_string(date.getDay())+"日"+accounts[index]->getId()+"取了"+to_string(amount)+"元,原因："+desc));
                        // 如果没有错误再进行写入文件
                        if(!is_now_reading_a_file) {
                            commands << endl << cmd << " ";
                            commands << index << " " << amount << " " << desc;
                        }
                    }
                    catch (AccountException& err){
                        cerr << err.what() << endl;
                        QMessageBox::warning(iw,tr("警告信息"),tr("你没这么多钱，你居然还取，乐死我了"));
                    }
                    catch (runtime_error& err) {
                        cerr << err.what() << endl;
                    }
                    break;
                case 's'://查询各账户信息
                    static unsigned int num;
                    num = 1;
                    for (size_t i = 0; i < accounts.size(); i++) {
//                        cout << "[" << i << "] ";
//                        accounts[i]->show();
//                        cout << endl;
                        if(accounts[i]->getUser() == MainWindow::Log_on_User) // 进行用户过滤
                            iw->ui->textBrowser1->append(QString::fromStdString("[" + to_string(num++) + "] " + accounts[i]->show()));
                    }
                    break;
                case 'c'://改变日期
                    if(is_now_reading_a_file) commands >> day;
                    else {
                        //cin >> day;
                        day = day_change;
                    }
                    if (day < date.getDay()){
                        cerr << "You cannot specify a previous day" << endl;
                        QMessageBox::warning(iw,tr("警告信息"),tr("时光不能倒流。"));
                    }
                    else if (day > date.getMaxDay()){
                        cerr << "Invalid day" << endl;
                        QMessageBox::warning(iw,tr("警告信息"),tr("超出了当月最大日期"));
                    }
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
                        date1 = q1;
                        date2 = q2;
                        iw->ui->textBrowser1->append(QString::fromStdString(Account::query(date1, date2, MainWindow::Log_on_User)));
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
}

void InsideWindow::on_pushButton_vhhu_clicked()
{
    aa[1] = ui->id->text();
    for(auto &iter : accounts){
        if(iter->getId() == aa[1].toStdString()){
            QMessageBox::warning(this,tr("警告信息"),tr("系统中已有重名账号"));
            return;
        }
    }
    if(ui->checkBox->checkState() == Qt::Checked){
        aa[0] = "c";
    }
    else aa[0] = "s";
    aa[2] = ui->credit->text();
    aa[3] = ui->rate->text();
    aa[4] = ui->fare->text();
    InsideWindow::backMain('a', false);
}

void InsideWindow::on_pushButton_cyqm_clicked()
{
    ddww[0] = ui->id_cy->text();
    for(unsigned int i=0; i < accounts.size(); i++){
        if(accounts[i]->getId() == ddww[0].toStdString()){
            if(accounts[i]->getUser() != MainWindow::Log_on_User){
                QMessageBox::warning(this,tr("警告信息"),tr("非法操作：这不是你的账号"));
                return;
            }
            ddww[0] = (char)i+48;
            ddww[1] = ui->amount_cy->text();
            ddww[2] = ui->desc_cy->text();
            InsideWindow::backMain('d',false);
            return;
        }
    }
    QMessageBox::warning(this,tr("警告信息"),tr("系统中找不到此账号"));
}

void InsideWindow::on_pushButton_quqm_clicked()
{
    ddww[0] = ui->id_qu->text();
    for(unsigned int i=0; i < accounts.size(); i++){
        if(accounts[i]->getId() == ddww[0].toStdString()){
            if(accounts[i]->getUser() != MainWindow::Log_on_User){
                QMessageBox::warning(this,tr("警告信息"),tr("非法操作：这不是你的账号"));
                return;
            }
            ddww[0] = (char)i+48;
            ddww[1] = ui->amount_qu->text();
            ddww[2] = ui->desc_qu->text();
            InsideWindow::backMain('w',false);
            return;
        }
    }
    QMessageBox::warning(this,tr("警告信息"),tr("系统中找不到此账号"));
}

void InsideWindow::on_pushButton_gdbmriqi_clicked()
{
    day_change = ui->day_change->text().toInt();
    InsideWindow::backMain('c',false);
}

void InsideWindow::on_pushButton_jbruxxgeyt_clicked()
{
    InsideWindow::backMain('n',false);
}

void InsideWindow::on_pushButton_iaxyxbxi_clicked()
{
    InsideWindow::backMain('s',false);
}

void InsideWindow::on_pushButton_iaxyvhmu_clicked()
{
    q1 = Date(ui->dateEdit1->date().year(), ui->dateEdit1->date().month(), ui->dateEdit1->date().day());
    q2 = Date(ui->dateEdit2->date().year(), ui->dateEdit2->date().month(), ui->dateEdit2->date().day());
    InsideWindow::backMain('q',false);
}

//wulmwh212bjwhgricvizo.veuiyigeuvyb.

void InsideWindow::jisrBro2(){
    double ykhr = 0;
    double uzru = 0, viiu = 0;
    for(unsigned int i=0; i < accounts.size(); i++){
        if(accounts[i]->getUser() == MainWindow::Log_on_User){
            if(accounts[i]->s_or_c()){//信用卡
                ykhr += accounts[i]->getDebt();
            }
        }
    }
    //cout << date.getYear()<<date.getMonth()-1<<1
    uzru = Account::iaxy_uzru(Date(date.getYear(),date.getMonth(),1),Date(date.getYear(),date.getMonth(),date.getMaxDay()),MainWindow::Log_on_User);
    viiu = Account::iaxy_viiu(Date(date.getYear(),date.getMonth(),1),Date(date.getYear(),date.getMonth(),date.getMaxDay()),MainWindow::Log_on_User);
    iw->ui->textBrowser2->append(QString::fromStdString("本月应还："+to_string(ykhr)+" 本月收入："+to_string(uzru)+" 本月支出"+to_string(viiu)));
}



// 在insidewindow创建一个静态成员函数，统一处理，分别调用。
//    bool is_now_reading_a_file = true; // 1为正在读取文件，0为手动添加命令并且添加到文件内模式
//    static bool only_show_once = false;
//    Date date(2008, 11, 1); // 起始日期
//    vector<Account *> accounts; // 创建账户数组，元素个数为0
//    char cmd;
//    fstream commands;
//    commands.open("commands.txt", ios_base::in | ios_base::out);
//    if(!commands.is_open()){
//        // 文件打开失败
//        commands.open("commands.txt",ios_base::out | ios_base::app);
//        cout << "File cannot open or there is no such a command.txt. It will create a new file." << endl;
//        is_now_reading_a_file = false;
//    }
//    do {
//        if(cin.fail()) return 0;
//        if(is_now_reading_a_file && commands.eof()){
//            commands.clear();
//            //commands << endl;
//            is_now_reading_a_file = false;
//        }
//        if (!is_now_reading_a_file && !only_show_once) {
//            cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit"
//                << endl;
//            only_show_once = true;
//        }
////显示日期和总金额
//        if(!is_now_reading_a_file){
//            date.show();
//            cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";
//        }
//        char type;
//        int index, day;
//        double amount, credit, rate, fee;
//        string id, desc;
//        Account* account;
//        Date date1{}, date2{};
//        if(is_now_reading_a_file) commands >> cmd;
//        else {
//            cin >> cmd;
//            //if(cmd != 'e' && cmd != 's')
//            //    commands << endl << cmd << " ";
//        }
//        switch (cmd) {
//            case 'a'://增加账户
//                if(is_now_reading_a_file)
//                    commands >> type >> id;
//                else {
//                    try{
//                        cin >> type >> id;
//                        if(type == 's' || type == 'c'){
//                            commands << endl << cmd << " ";
//                            commands << type << " " << id << " ";
//                        }
//                        else throw runtime_error("Not a saving or credit account.");
//                    }
//                    catch (runtime_error& err) {
//                        cerr << err.what() << endl;
//                    }
//                }
//                if (type == 's') {
//                    if(is_now_reading_a_file) commands >> rate;
//                    else {
//                        cin >> rate;
//                        commands << rate;
//                    }
//                    account = new SavingsAccount(date, id, rate);
//                }
//                else {
//                    if(is_now_reading_a_file) commands >> credit >> rate >> fee;
//                    else {
//                        cin >> credit >> rate >> fee;
//                        commands << credit << " " << rate << " " << fee;
//                    }
//                    account = new CreditAccount(date, id, credit, rate, fee);
//                }
//                accounts.push_back(account);
//                break;
//            case 'd'://存入现金
//                try{
//                    if(is_now_reading_a_file){
//                        commands >> index >> amount;
//                        getline(commands, desc);
//                    }
//                    else{
//                        cin >> index >> amount;
//                        getline(cin, desc);
//                        if(index < 0 || index >= accounts.size()){
//                            throw runtime_error("The index you input is not exist.");
//                        }
//                        commands << endl << cmd << " ";
//                        commands << index << " " << amount << " " << desc;
//                    }
//                    accounts[index]->deposit(date, amount, desc);
//                }
//                catch (runtime_error& err) {
//                    cerr << err.what() << endl;
//                }
//                break;
//            case 'w'://取出现金
//                try{
//                    if(is_now_reading_a_file){
//                        commands >> index >> amount;
//                        getline(commands, desc);
//                    }
//                    else{
//                        cin >> index >> amount;
//                        getline(cin, desc);
//                        if(index < 0 || index >= accounts.size()){
//                            throw runtime_error("The index you input is not exist.");
//                        }
//                    }
//                    accounts[index]->withdraw(date, amount, desc);
//                    // 如果没有错误再进行写入文件
//                    if(!is_now_reading_a_file) {
//                        commands << endl << cmd << " ";
//                        commands << index << " " << amount << " " << desc;
//                    }
//                }
//                catch (AccountException& err){
//                    cerr << err.what() << endl;
//                }
//                catch (runtime_error& err) {
//                    cerr << err.what() << endl;
//                }
//                break;
//            case 's'://查询各账户信息
//                for (size_t i = 0; i < accounts.size(); i++) {
//                    cout << "[" << i << "] ";
//                    accounts[i]->show();
//                    cout << endl;
//                }
//                break;
//            case 'c'://改变日期
//                if(is_now_reading_a_file) commands >> day;
//                else {
//                    cin >> day;
//                }
//                if (day < date.getDay())
//                    cerr << "You cannot specify a previous day" << endl;
//                else if (day > date.getMaxDay())
//                    cerr << "Invalid day" << endl;
//                else {
//                    date = Date(date.getYear(), date.getMonth(), day);
//                    if(!is_now_reading_a_file) {
//                        commands << endl << cmd << " ";
//                        commands << day;
//                    }
//                }
//                break;
//            case 'n'://进入下个月
//                if(!is_now_reading_a_file)
//                    commands << endl << cmd << " ";
//                if (date.getMonth() == 12)
//                    date = Date(date.getYear() + 1, 1, 1);
//                else
//                    date = Date(date.getYear(), date.getMonth() + 1, 1);
//                for (auto & iter : accounts)
//                    iter->settle(date);
//                break;
//            case 'q'://查询一段时间内的账目
//                try {
//                    date1 = Date::read();
//                    date2 = Date::read();
//                    Account::query(date1, date2);
//                }
//                catch (DateException& err){
//                    cerr << err.what() << endl;
//                    if(cin.fail()) cin.clear();
//                }
//                break;
//            default:
//                cerr << "Not a right command." <<endl;
//                break;
//        }
//    } while (cmd != 'e');
//    for_each(accounts.begin(), accounts.end(), deleter());
//    commands.close();
