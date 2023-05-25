#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "gameui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_clicked()
{
    static GameUI w1;
    w1.setStyleSheet("background-color: #fbecde");
    QObject::connect(this,SIGNAL(showGameUI()),&w1,SLOT(recvGameUI()));
    //qDebug() << QString::fromStdString( Log_on_User );
    this->hide(); //隐藏本页面
    emit showGameUI(); //激活信号
}
