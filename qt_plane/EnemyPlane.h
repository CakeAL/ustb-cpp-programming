//
// Created by CakeAL on 2023/5/11.
//

#ifndef PLANEBATTLE_ENEMYPLANE_H
#define PLANEBATTLE_ENEMYPLANE_H
#include <vector>
#include "Bullet.h"

class EnemyPlane {
public:
    EnemyPlane();
    void printEnemy() const;
    void clearEnemy() const;
    static void spawnAnEnemy(); // 生成一个敌机
    static void moveEnemy(); //每半秒，飞机向下移动一格
    static void spawnABullet(Ui::GameUI *ui, QWidget *widget, GameUI *gameui);

    static int max_enemy;
    static int id;
    int x, y; //当前敌机坐标
    int the_id;
    static std::vector<EnemyPlane> enemys;
    static std::vector<Bullet> enemysBullet;
};


#endif //PLANEBATTLE_ENEMYPLANE_H
