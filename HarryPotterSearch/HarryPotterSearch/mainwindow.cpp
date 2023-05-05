#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "fstream"
#include "cstdio"
#include "QString"
#include "string"
#include "vector"
#include "QMessageBox"

using namespace std;

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

vector<SearchInfo> searchInfo;
const char *books[8] = {
    "J.K. Rowling - Quidditch Through the Ages.txt",
    "J.K. Rowling - HP 6 - Harry Potter and the Half-Blood Prince.txt",
    "J.K. Rowling - HP 4 - Harry Potter and the Goblet of Fire.txt",
    "J.K. Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban.txt",
    "J.K. Rowling - HP 0 - Harry Potter Prequel.txt",
    "HP7--Harry_Potter_and_the_Deathly_Hallows_Book_7_.txt",
    "HP2--Harry_Potter_and_the_Chamber_of_Secrets_Book_2_.txt",
    "J.K. Rowling - The Tales of Beedle the Bard.txt"
};

// 点击查找按钮
void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear(); //清屏
    searchInfo.clear(); //清空上一次查找的缓存
    QString text = ui->lineEdit->text(); //获取输入文本
    int num = 0;
    for(int i = 0; i < 8; i++) {
        fstream file;
        file.open(books[i], ios::in);
        if (!file.is_open()) {
           cerr << "文件打开失败" << endl;
        }
        char name[100];
        char buf[1024] = {0};
        string chapter = "CHAPTER";
        string chapter1 = "Chapter";
        int cur_chapter = 0;
        int cur_page = 0;
        //scanf("%s", name); //输入查找的姓名
        strcpy(name, text.toStdString().c_str()); //转换用来查找的姓名
        while (file.getline(buf, sizeof(buf))) {
            if(buf[0] == 0 && (buf[1] == '\r' || buf[1] == '\n')) continue;
            try {
                if (buf[0] == chapter[0] && buf[1] == chapter[1] && buf[2] == chapter[2] &&
                        buf[3] == chapter[3] && buf[4] == chapter[4] && buf[5] == chapter[5] && buf[6] == chapter[6]) {
                    cur_chapter++;
                    continue;
                } else if (buf[3] == chapter[0] && buf[4] == chapter[1] && buf[5] == chapter[2] &&
                           buf[6] == chapter[3] && buf[7] == chapter[4] && buf[8] == chapter[5] && buf[9] == chapter[6]){
                    cur_chapter++; //用于跳过开头utf-8标识
                    continue;
                } else if(buf[0] == chapter1[0] && buf[1] == chapter1[1] && buf[2] == chapter1[2] &&
                        buf[3] == chapter1[3] && buf[4] == chapter1[4] && buf[5] == chapter1[5] && buf[6] == chapter1[6]) {
                    cur_chapter++;
                    continue;
                } else if (buf[3] == chapter1[0] && buf[4] == chapter1[1] && buf[5] == chapter1[2] &&
                           buf[6] == chapter1[3] && buf[7] == chapter1[4] && buf[8] == chapter1[5] && buf[9] == chapter1[6]){
                    cur_chapter++; //用于跳过开头utf-8标识
                    continue;
                }else if (stoi(string(buf)) && stoi(string(buf)) == cur_page + 1) { //判断是否一行都是数字，一行都是数字说明是页码
                    cur_page++;
                    continue;
                }
            }  catch (...) {
                //do nothing
            }
            char *buf_point = buf;
            while (*buf_point != 0) {
                if (*buf_point == *name) {
                    int p = 0;
                    int sign = 1;
                    while(*(name+p) != 0){
                        if(*(name+p) != *(buf_point+p)){
                            sign = 0;
                            break;
                        }
                        p++;
                    }
                    if (sign == 0) {
                        buf_point++;
                        continue;
                    } else {
                        //cout << cur_page << " " << cur_chapter << " " << endl << buf << endl;
                        searchInfo.push_back(SearchInfo(i, cur_page, cur_chapter, string(buf)));
                        ui->textBrowser->append(QString::fromStdString("<a href='" + to_string(++num) + "'>" + to_string(num) + "</a>"+ "&nbsp;&nbsp;&nbsp;&nbsp;" + name + "&nbsp;&nbsp;&nbsp;&nbsp;" + to_string(cur_page) + "&nbsp;&nbsp;&nbsp;&nbsp;" + to_string(cur_chapter) + "&nbsp;&nbsp;&nbsp;&nbsp;"+ string(books[i])));
                    }
                }
                buf_point++;
            }
        }
        file.close();
    }
}


SearchInfo::SearchInfo(int bookNum, int page, int chapter, std::string line):bookNum(bookNum), page(page), chapter(chapter), line(line)
{

}

SearchInfo::~SearchInfo(){}

string SearchInfo::getLine()
{
    return this->line;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString text = ui->lineEdit_2->text();//获取查询的text
    int num = 0;
    try {
        num = stoi(text.toStdString());
    }  catch (...) {
        QMessageBox::warning(this,tr("警告信息"),tr("请输入正确的编号"));
    }
    num--;
    if(num >= int(searchInfo.size())){
        QMessageBox::warning(this,tr("警告信息"),tr("输入的编号过大"));
        return;
    }
    ui->textBrowser_2->clear();
    ui->textBrowser_2->append(QString::fromStdString(searchInfo[num].getLine()));
}


void MainWindow::on_textBrowser_anchorClicked(const QUrl &arg1)
{
        ui->textBrowser->setOpenExternalLinks(false);
        ui->textBrowser->setOpenLinks(false);
        QString clickedText = arg1.toString();
        //cout << clickedText.toStdString() << endl;
        int num = stoi(clickedText.toStdString()) - 1;
        ui->textBrowser_2->clear();
        ui->textBrowser_2->append(QString::fromStdString(searchInfo[num].getLine()));
}

