#include "gameui.h"
#include "ui_gameui.h"
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <Qdir>
#include <QTimer>
#include <QKeyEvent>
#include <QThread>


#include "MyPlane.h"
#include "EnemyPlane.h"
#include "TheMap.h"
#include "Bullet.h"
#include <vector>
#include <iostream>
#include <conio.h>

void mainloop(Ui::GameUI *ui);

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

GameUI::GameUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameUI)
{
    par_widget = parent;
    ui->setupUi(this);
    QLabel *MyplaneLabel= ui->Myplane;
    QPixmap mypng("Myplane.png");
    //    QString newDirectory = "/";
    //    QDir::setCurrent(newDirectory);
    //    QString currentPath = QDir::currentPath();
    //    qDebug() << "Current Path: " << currentPath;
    if(mypng.isNull()){
        qDebug() << "Failed to load image!";
    }
    QSize newSize(50, 50);
    mypng = mypng.scaled(newSize, Qt::KeepAspectRatio);
    MyplaneLabel->setPixmap(mypng);
    MyplaneLabel->setAlignment(Qt::AlignCenter);
    MyplaneLabel->move(36*10,30*30); // 10 and 30

    // 初始化飞机位置
    MyPlane::printPlane(X, Y, MyplaneLabel); //35,27
    TheMap::printPoints();

    //开启键盘处理
    setFocusPolicy(Qt::StrongFocus);

    // 在构造函数中创建定时器
    QTimer* timer = new QTimer(this);

    // 将定时器的超时信号连接到 mainloop() 槽函数
    connect(timer, &QTimer::timeout, this, &GameUI::mainloop);

    // 启动定时器，设置时间间隔为50毫秒
    timer->start(50);

}

GameUI::~GameUI()
{
    delete ui;
}

void GameUI::recvGameUI(){
    this->show();
}

char key;
void GameUI::mainloop(){
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
            EnemyPlane::spawnABullet(ui, par_widget, this);
            enemy_spawn_Bullet = 0;
        }
        //Sleep(50); //游戏fps 20
        //QThread::msleep(50);
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
        MyPlane::movePlane(X, Y, ui, key, par_widget, this);
        static unsigned int sign_points = 0;
        if(sign_points != MyPlane::getPoints()){
            TheMap::printPoints();
            sign_points = MyPlane::getPoints();
        }
//        if(EnemyPlane::max_enemy == 0 || MyPlane::getPoints() == 0){
//            break;
//        }
//    ConsoleOperator::gotoXY(1,1);
//    std::cout << "Game Over!\nParse \"Q\" to exit.";
//    //system("pause");
//    while(true){
//        if (_kbhit()){
//            int key = _getch();
//            if(key == 'q') break;
//        }
//    }
//        // 停止定时器，防止重复调用 mainloop()
//        QTimer::singleShot(0, this, [this]() {
//            sender()->deleteLater();
//        });
}

void GameUI::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        // 处理按下W键的操作
        key = 'w';
        break;
    case Qt::Key_A:
        // 处理按下A键的操作
        key = 'a';
        break;
    case Qt::Key_S:
        // 处理按下S键的操作
        key = 's';
        break;
    case Qt::Key_D:
        // 处理按下D键的操作
        key = 'd';
        break;
    case Qt::Key_Space:
        // 处理按下空格键的操作
        key = ' ';
        break;
    default:
        // 其他按键的处理
        key = '\0';
        break;
    }
}

void GameUI::keyReleaseEvent(QKeyEvent *event)
{
    key = '\0';
}

