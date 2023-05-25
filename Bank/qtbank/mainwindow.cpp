#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vector"
#include "bankusers.h"
#include "QLineEdit"
#include "QDebug"
#include "fstream"
#include "string"
#include "md5.h"
#include "iostream"
#include "QMessageBox"
#include "QDir"
#include "insidewindow.h"
using namespace std;

string MainWindow::Log_on_User;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fstream users;
    users.open("users.txt", ios_base::in);
    while(!users.eof() && users.is_open()){
        string id,password;
        users >> id >> password;
        bankUsers.push_back(new BankUsers(id,password));
    }
    users.close();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_registerID_clicked()
{
    fstream users;
    users.open("users.txt", ios_base::out | ios_base::app);
    //QDir temdir("users.txt");
    //QString filePath = temdir.absoluteFilePath("users.txt");
    //qDebug() << filePath;
    QString id = ui->inputID->text();
    QString password = ui->inputPassword->text();
    //qDebug() << users.is_open();
    for(auto &iter : bankUsers){
        if(iter->getID() == id.toStdString()){
            QMessageBox::warning(this,tr("警告信息"),tr("系统中已有重名用户"));
            return;
        }
    }
    users << id.toStdString() << " " << MD5(password.toStdString()).toString() << endl;
    //qDebug() << id << " " << password;
    bankUsers.push_back(new BankUsers(id.toStdString(), MD5(password.toStdString()).toString()));
    users.close();
    //std::cout << id.toStdString() << MD5(password.toStdString()).toString();

}


void MainWindow::on_log_onID_clicked()
{
    QString id = ui->inputID->text();
    QString password = ui->inputPassword->text();
    for(auto &iter : bankUsers){
        if(iter->getID() == id.toStdString()){
            if(iter->getPassword() == MD5(password.toStdString()).toString()){
                //qDebug() << 1;
                Log_on_User = iter->getID();
                static InsideWindow w1;
                QObject::connect(this,SIGNAL(showInsideWindow()),&w1,SLOT(recvInsideWindow()));
                //qDebug() << QString::fromStdString( Log_on_User );
                this->hide(); //隐藏本页面
                    emit showInsideWindow(); //激活信号
            }
            else {
                QMessageBox::warning(this,tr("警告信息"),tr("密码错误"));
            }
            return;
        }
    }
    QMessageBox::warning(this,tr("警告信息"),tr("系统中查无此户"));
    return;
}

