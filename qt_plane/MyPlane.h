//
// Created by CakeAL on 2023/5/11.
//

#ifndef PLANEBATTLE_MYPLANE_H
#define PLANEBATTLE_MYPLANE_H
#include <vector>
#include "Bullet.h"
#include <QLabel>

class MyPlane {
public:
    MyPlane();
    static unsigned int getPoints(); //获得分数
    static void printPlane(int x, int y, QLabel *myPlaneLabel); //打印飞机
    static void movePlane(int& x, int& y, Ui::GameUI *ui, char key, QWidget *widget, GameUI *gameui); //进行检测按键，同时移动飞机
    static void clearPlane(int x, int y); //清除上一帧的飞机
    static void spawnABullet(int x, int y, Ui::GameUI *ui, QWidget *widget, GameUI *gameui);

    static std::vector<Bullet> myPlaneBullet;
    static unsigned int points; //我方分数
};


#endif //PLANEBATTLE_MYPLANE_H
