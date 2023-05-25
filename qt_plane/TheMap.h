//
// Created by CakeAL on 2023/5/11.
//

#ifndef PLANEBATTLE_THEMAP_H
#define PLANEBATTLE_THEMAP_H


class TheMap {
public:
    // map中标记1为我方，2为敌机，3为我方子弹，4为敌方子弹
    static int map[40][60]; //战场地图，高度为35(2~36)，宽度为55(3~58)，括号内为对应使用的二维数组的值
    static int bulletMap[40][60]; //子弹地图
    static void printPoints();
};


#endif //PLANEBATTLE_THEMAP_H
