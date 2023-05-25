//
// Created by CakeAL on 2023/5/14.
//

#include "Bullet.h"
#include "TheMap.h"
#include <iostream>
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <ui_gameui.h>
#include <QWidget>
#include "MyPlane.h"
#include "EnemyPlane.h"
#include "gameui.h"
#include <QList>
#include <QDebug>
#include <string>

int name = 0;
Bullet::Bullet(int bulletType, int x, int y, Ui::GameUI *ui, QWidget *widget, GameUI *gameui): bulletType(bulletType), x(x), y(y) {
    TheMap::bulletMap[x][y] = bulletType;
    QLabel *bulletLabel = new QLabel(ui->Myplane);
    bulletLabel->setObjectName(std::to_string(name));
    this->bulletLabel = bulletLabel;
    QPixmap mypng("bullet.png");
    if(mypng.isNull()){
        qDebug() << "Failed to load image!";
    }
    QSize newSize(30, 30);
    mypng = mypng.scaled(newSize, Qt::KeepAspectRatio);
    this->bulletLabel->setPixmap(mypng);
    this->bulletLabel->setAlignment(Qt::AlignCenter);
    this->bulletLabel->move(0,0); // 10 and 30
}

void Bullet::printBullet() const {
//    ConsoleOperator::gotoXY(x, y);
//    std::cout << ".";
    TheMap::bulletMap[x][y] = bulletType;
}

void Bullet::clearBullet() const {
//    ConsoleOperator::gotoXY(x, y+1);
//    std::cout << "\b ";
    TheMap::bulletMap[x][y] = 0;
}

void Bullet::moveUpBullet() {
    for (auto it = MyPlane::myPlaneBullet.begin(); it != MyPlane::myPlaneBullet.end();){
        it->clearBullet();
        it->x -= 1;
        if(TheMap::map[it->x][it->y] != 0 && TheMap::map[it->x][it->y] != 1000){
            meetEnemy(*it);
            it = MyPlane::myPlaneBullet.erase(it);
            continue;
        }
        if(it->x <= 0){
            //子弹走到最上面时删除这个子弹
            TheMap::bulletMap[it->x][it->y] = 0;
            it = MyPlane::myPlaneBullet.erase(it);
            continue;
        }
        it->printBullet();
        it++;
    }
}

// 我方子弹与敌机相撞后的处理
void Bullet::meetEnemy(Bullet &bullet) {
    //导致了意外终止
    //第一个飞机删除之后，TheMap::map[bullet.x][bullet.y]-1 还是这个飞机么？
    //EnemyPlane::enemys[TheMap::map[bullet.x][bullet.y]-1].clearEnemy();
    //EnemyPlane::enemys.erase(EnemyPlane::enemys.begin()+TheMap::map[bullet.x][bullet.y]-1);
    for (auto it = EnemyPlane::enemys.begin(); it != EnemyPlane::enemys.end(); it++) {
        if (it->the_id == TheMap::map[bullet.x][bullet.y]){
            it->clearEnemy();
            EnemyPlane::enemys.erase(it);
            break;
        }
    }
    TheMap::map[bullet.x][bullet.y] = 0;
    TheMap::bulletMap[bullet.x][bullet.y] = 0;
    MyPlane::points++;
}

void Bullet::moveDownBullet() {
    for (auto it = EnemyPlane::enemysBullet.begin(); it != EnemyPlane::enemysBullet.end();){
        it->clearBullet();
        it->x += 1;
        if(TheMap::map[it->x][it->y] == 1000){
            MyPlane::points -= 1;
            it = EnemyPlane::enemysBullet.erase(it);
            continue;
        }
        if(it->x >= 38){
            //子弹走到最上面时删除这个子弹
            TheMap::bulletMap[it->x][it->y] = 0;
            it = EnemyPlane::enemysBullet.erase(it);
            continue;
        }
        it->printBullet();
        it++;
    }
}
