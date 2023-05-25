//
// Created by CakeAL on 2023/5/11.
//

#include "ConsoleOperator.h"
#include "windows.h"

void ConsoleOperator::gotoXY(int x, int y){ // 光标移动到x，y位置
    COORD pos = {(short)y, (short)x};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //获取标准输出句柄
    SetConsoleCursorPosition(hOut, pos);
}

void ConsoleOperator::HideCursor(){
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; //第二个值为0表示隐藏光标
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// 设置窗口控制台大小（需要使用旧版控制台）
void ConsoleOperator::SetConsoleWindowSize( short width, short height )
{
    HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT wrt = { 0, 0, static_cast<SHORT>(width-1), static_cast<SHORT>(height-1) };
    SetConsoleWindowInfo( hStdOutput, TRUE, &wrt ); // 设置窗体尺寸
    COORD coord = { width, height };
    SetConsoleScreenBufferSize( hStdOutput, coord ); // 设置缓冲尺寸
}