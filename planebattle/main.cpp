#include "ConsoleOperator.h"
#include "MyPlane.h"
#include "EnemyPlane.h"
#include "TheMap.h"
#include "Bullet.h"
#include <windows.h>
#include <vector>
#include <iostream>
#include <conio.h>

int TheMap::map[40][60] = {0};
int TheMap::bulletMap[40][60] = {0};
std::vector<EnemyPlane> EnemyPlane::enemys;
std::vector<Bullet> MyPlane::myPlaneBullet;
std::vector<Bullet> EnemyPlane::enemysBullet;
int EnemyPlane::max_enemy = 51;
int EnemyPlane::id = 0;
unsigned int MyPlane::points = 1;
// 初始化飞机坐标
int X = 35 + 1, Y = 27 + 3;

// 初始化相关参数
void init();

int main() {
    init();
    while(true){ //进行游戏控制
        static int if_update_Bullet = 0;
        if_update_Bullet++;
        if(if_update_Bullet == 2){ //每0.1s子弹刷新一遍
            Bullet::moveUpBullet();
            if_update_Bullet = 0;
        }
        static int if_update_down_Bullet = 0;
        if_update_down_Bullet++;
        if(if_update_down_Bullet == 6){ //每0.3s敌机子弹刷新一遍
            Bullet::moveDownBullet();
            if_update_down_Bullet = 0;
        }
        static int enemy_spawn_Bullet = 0;
        enemy_spawn_Bullet++;
        if(enemy_spawn_Bullet == 50){ // 每2.5s生成一个子弹
            EnemyPlane::spawnABullet();
            enemy_spawn_Bullet = 0;
        }
        Sleep(50); //游戏fps 20
        if(EnemyPlane::max_enemy != 0) {
            static int if_spawn = 0;
            if_spawn++;
            if (if_spawn == 50 * 2) { //5s生成一个敌机
                EnemyPlane::spawnAnEnemy();
                if_spawn = 0;
            }
        }
        static int if_move = 0;
        if_move++;
        if(if_move == 10) { //每0.5s敌机向下走一格
            EnemyPlane::moveEnemy();
            if_move = 0;
        }
        //system("cls"); //对控制台进行清屏
        MyPlane::movePlane(X, Y);
        static unsigned int sign_points = 0;
        if(sign_points != MyPlane::getPoints()){
            TheMap::printPoints();
            sign_points = MyPlane::getPoints();
        }
        if(EnemyPlane::max_enemy == 0 || MyPlane::getPoints() == 0){
            break;
        }
    }
    ConsoleOperator::gotoXY(1,1);
    std::cout << "Game Over!\nParse \"Q\" to exit.";
    //system("pause");
    while(true){
        if (_kbhit()){
            int key = _getch();
            if(key == 'q') break;
        }
    }
    return 0;
}

void init() {
    // 初始化窗口
    ConsoleOperator::HideCursor();
    ConsoleOperator::SetConsoleWindowSize(63, 40);
    // 初始化飞机位置
    MyPlane::printPlane(X, Y); //35,27
    TheMap::printPoints();
}