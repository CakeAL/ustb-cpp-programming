//
// Created by CakeAL on 2023/5/11.
//

#include "MyPlane.h"
#include "TheMap.h"
#include "ui_gameui.h"
#include <iostream>
#include <QLabel>
#include <QDebug>

//using Map = decltype(TheMap::map);
//Map &map = TheMap::map;

MyPlane::MyPlane()= default;

unsigned int MyPlane::getPoints() {
    return points;
}

void MyPlane::printPlane(int x, int y, QLabel *myPlaneLabel) {
//    ConsoleOperator::gotoXY(x-1, y-2); //移动到绘制开始区域
//    std::cout << " /=\\ "; //绘制飞机第一行
//    ConsoleOperator::gotoXY(x, y-2); //移动到飞机第二行开始区域
//    std::cout << "<<*>>"; //
//    ConsoleOperator::gotoXY(x+1, y-2);
//    std::cout << " * * ";
    myPlaneLabel->move(y*10, x*30);
    TheMap::map[x][y] = 1000;
}


void MyPlane::movePlane(int& x, int& y, Ui::GameUI *ui, char key, QWidget *widget, GameUI *gameui) {
    //qDebug() << "12";
    if(key != '\0'){ //检测是否有键盘输入
        //clearPlane(x, y); //检测到有键盘输入才进行清楚
        //int key = _getch(); //从键盘获取输入内容
        if(key == 'w'){
            if(x >= 2) x-=1;
        } else if (key == 's'){
            if(x <= 36) x+=1;
        } else if (key == 'a'){
            if(y >= 3) y-=1;
        } else if (key == 'd'){
            if(y <= 58) y+=1;
        } else if (key == ' '){ //空格键
            spawnABullet(x, y, ui, widget, gameui);
        }
        printPlane(x, y, ui->Myplane); //绘制飞机
    }
}

void MyPlane::clearPlane(int x, int y) {
//    ConsoleOperator::gotoXY(x-1, y+3); //移动到第一行最后面
//    std::cout << "\b\b\b\b\b"; //删除飞机第一行
//    std::cout << "     "; //用空格当占位符
//    ConsoleOperator::gotoXY(x, y+3); //移动到第二行最后面
//    std::cout << "\b\b\b\b\b"; //删除飞机第二行
//    std::cout << "     "; //用空格当占位符
//    ConsoleOperator::gotoXY(x+1, y+3);
//    std::cout << "\b\b\b\b\b"; //删除飞机第三行
//    std::cout << "     "; //用空格当占位符
    TheMap::map[x][y] = 0;
}

void MyPlane::spawnABullet(int x, int y, Ui::GameUI *ui, QWidget *widget, GameUI *gameui) {
    myPlaneBullet.emplace_back(3, x-2, y, ui, widget, gameui);
    myPlaneBullet.back().printBullet();
}
