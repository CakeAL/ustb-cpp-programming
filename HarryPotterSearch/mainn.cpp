//
// Created by cakeal on 2023/4/27.
//
#include "iostream"
#include "fstream"
#include "cstdio"

using namespace std;

int main() {
    fstream file;
    file.open("HarryPotterSearch/J.K. Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban.txt", ios::in);
    if (!file.is_open()) {
        cerr << "文件打开失败" << endl;
    }
    char name[100];
    char buf[1024] = {0};
    string chapter = "CHAPTER";
    int cur_chapter = -1;
    int cur_page = 0;
    scanf("%s", name); //输入查找的姓名
    while (file.getline(buf, sizeof(buf))) {
        if(buf[0] == 0 && (buf[1] == '\r' || buf[1] == '\n')) continue;
        if (buf[0] == chapter[0] && buf[1] == chapter[1] && buf[2] == chapter[2] &&
                buf[3] == chapter[3] && buf[4] == chapter[4] && buf[5] == chapter[5] && buf[6] == chapter[6]) {
            cur_chapter++;
            continue;
        } else if (buf[3] == chapter[0] && buf[4] == chapter[1] && buf[5] == chapter[2] &&
                   buf[6] == chapter[3] && buf[7] == chapter[4] && buf[8] == chapter[5] && buf[9] == chapter[6]){
            cur_chapter++; //用于跳过开头utf-8标识
            continue;
        }else if (buf[0] >= '0' && buf[0] <= '9') {
            cur_page++;
            continue;
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
                    cout << cur_page << " " << cur_chapter << " " << endl << buf << endl;
                }
            }
            buf_point++;
        }
    }
    file.close();
    return 0;
}