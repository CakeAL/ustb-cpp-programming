//
// Created by CakeAL on 2023/5/11.
//

#include "EnemyPlane.h"
#include "TheMap.h"
#include <iostream>
#include <random>
#include <ctime>
#include <vector>

EnemyPlane::EnemyPlane() {
    // 使用随机数生成一个飞机随机分布在y在2~36的位置
    std::default_random_engine randNum;
    randNum.seed(time(nullptr));
    unsigned int yy = randNum() % 59;
    // 如果生成的坐标小于2，或者该位置的周围有敌机，重新生成一个
    while(yy <= 2 || TheMap::map[2][yy] == 2 || TheMap::map[2][yy+1] == 2 || TheMap::map[2][yy-1]
        || TheMap::map[2][yy-2] == 2 || TheMap::map[2][yy+2]) {
        yy = randNum() % 59;
    }
    this->y = (int)yy;
    this->x = 0;
    the_id = ++id;
    TheMap::map[x][y] = the_id; //当前坐标写入敌机
}

void EnemyPlane::printEnemy() const {
//    ConsoleOperator::gotoXY(x, y-1); //移动到开始绘制区域
//    std::cout << "\\+/"; //绘制敌机第一行
//    ConsoleOperator::gotoXY(x+1, y); //移动到第二行中间
//    std::cout << "|"; //
    TheMap::map[x][y] = the_id; //当前位置被占据
}

void EnemyPlane::clearEnemy() const {
//    ConsoleOperator::gotoXY(x, y+2); //移动到第一行末尾
//    std::cout << "\b\b\b";
//    std::cout << "   ";
//    ConsoleOperator::gotoXY(x+1, y+1);
//    std::cout << "\b";
//    std::cout << " ";
    TheMap::map[x][y] = 0; //当前位置被释放
}

void EnemyPlane::spawnAnEnemy(){
    if(max_enemy != 0) {
        enemys.emplace_back();
        enemys.back().printEnemy();
        max_enemy--;
    }
}

void EnemyPlane::moveEnemy() {
    // 遍历所有敌机，往下走一格
    for (auto it = enemys.begin(); it != enemys.end(); it++) {
        it->clearEnemy();
        it->x += 1;
        if(it->x >= 36) {
            //敌机走到最下面的时候删除这个敌机
            enemys.erase(it);
            continue;
        }
        it->printEnemy();
    }
}

void EnemyPlane::spawnABullet(Ui::GameUI *ui, QWidget *widget, GameUI *gameui) {
    for(auto it = enemys.begin(); it != enemys.end(); it++){
        enemysBullet.emplace_back(4, it->x+2, it->y, ui, widget, gameui);
        enemysBullet.back().printBullet();
    }
}
