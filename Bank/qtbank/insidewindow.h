#ifndef INSIDEWINDOW_H
#define INSIDEWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class InsideWindow;
}

class InsideWindow : public MainWindow
{
    Q_OBJECT

public:
    explicit InsideWindow(QWidget *parent = nullptr);
    ~InsideWindow();

private slots:
    void recvInsideWindow();

    void on_pushButton_vhhu_clicked();

    void on_pushButton_cyqm_clicked();

    void on_pushButton_quqm_clicked();

    void on_pushButton_gdbmriqi_clicked();

    void on_pushButton_jbruxxgeyt_clicked();

    void on_pushButton_iaxyxbxi_clicked();

    void on_pushButton_iaxyvhmu_clicked();

private:
    Ui::InsideWindow *ui;
    static InsideWindow *iw;
    static void backMain(char cmd, bool is_now_reading_a_file);
    static void jisrBro2();
};

#endif // INSIDEWINDOW_H
