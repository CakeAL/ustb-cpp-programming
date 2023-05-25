//
// Created by CakeAL on 2023/5/11.
//

#ifndef PLANEBATTLE_CONSOLEOPERATOR_H
#define PLANEBATTLE_CONSOLEOPERATOR_H


class ConsoleOperator {
public:
    static void gotoXY(int x, int y);
    static void HideCursor();
    static void SetConsoleWindowSize( short width, short height );
};


#endif //PLANEBATTLE_CONSOLEOPERATOR_H
