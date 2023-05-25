//
// Created by CakeAL on 2023/5/14.
//

#ifndef PLANEBATTLE_BULLET_H
#define PLANEBATTLE_BULLET_H
#include <QLabel>
#include "gameui.h"

class Bullet {
public:
    Bullet(int bulletType, int x, int y, Ui::GameUI *ui, QWidget *widget, GameUI *gameui);
    void printBullet() const;
    void clearBullet() const;
    static void moveUpBullet();
    static void meetEnemy(Bullet &bullet);
    static void moveDownBullet();

    int bulletType; // 3为我方子弹，4为敌方子弹
    int x;
    int y;
    QLabel *bulletLabel;
};


#endif //PLANEBATTLE_BULLET_H
