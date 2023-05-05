#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "string"
using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_textBrowser_anchorClicked(const QUrl &arg1);

private:
    Ui::MainWindow *ui;
};

class SearchInfo {
private:
    int bookNum; //书名的序号
    int page; //页数
    int chapter; //章节
    string line; //当前行的内容
public:
    SearchInfo(int bookNum, int page, int chapter, string line);
    ~SearchInfo();
    string getLine();
};

#endif // MAINWINDOW_H
