//
// Created by cakeal on 2023/4/21.
//
#include <iostream>
#include <vector>
//#include <algorithm>
using namespace std;

class Point2D{
protected:
    int x;
    int y;
public:
    Point2D(int x, int y);
};

Point2D::Point2D(int x, int y) : x(x), y(y){
}

class Creature : public Point2D{
private:
    static int theID;
    int ID;
    string name;
public:
    Creature(string name, int x, int y);
    void ShowCreatureInfo();
    void MoveCreature(int x, int y);
};

Creature::Creature(string name, int x, int y) : name(std::move(name)), Point2D(x,y){
    this->ID = theID++;
}

void Creature::ShowCreatureInfo() {
    cout << "No. " << ID << " creature " << name << " is at (" << x << ", " << y << ")" << endl;
}

void Creature::MoveCreature(int x, int y) {
    this->x = x;
    this->y = y;
}

int Creature::theID = 0; //初始化静态类变量
vector<Creature> creatures;

int main(){
    char cmd;
    string name;
    int x, y;
    while (true){
        cin >> cmd;
        switch (cmd) {
            case 'n':
                cin >> name >> x >> y;
                //creatures.push_back(Creature(name, x, y));
                creatures.emplace_back(name, x, y);
                break;
            case 'a':
                for (auto creature : creatures) {
                    creature.ShowCreatureInfo();
                }
                break;
            case 'm':
                int num;
                cin >> num >> x >> y;
                creatures[num].MoveCreature(x, y);
                break;
            case 's':
                cin >> num;
                creatures[num].ShowCreatureInfo();
                break;
            default:
                return 0;
        }
    }
}