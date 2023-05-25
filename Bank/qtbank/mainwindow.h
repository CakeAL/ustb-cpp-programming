#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vector"
#include "bankusers.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static string Log_on_User;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_registerID_clicked();

    void on_log_onID_clicked();

signals:
    void showInsideWindow();

private:
    Ui::MainWindow *ui;
protected:
    vector<BankUsers *> bankUsers;
};
#endif // MAINWINDOW_H
