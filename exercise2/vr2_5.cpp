//
// Created by cakeal on 2023/4/20.
//
#include <iostream>
#include <algorithm>

using namespace std;

int T, MaxMem;
int handle = 0; //句柄handle（句柄即内存块编号，分配的第一个内存块编号为1，以此类推）
int simMem[10010];
int sizeMem[10010];
int nowSizeOfMem = 0;

int main() {
    cin >> T >> MaxMem;
    string cmd;
    for (int i = 0; i < T; i++) {
        cin >> cmd;
        if (cmd == "new") {
            int size;
            cin >> size;
            nowSizeOfMem += size; //计算new之后的总内存大小
            if(nowSizeOfMem <= MaxMem){ //是否超过MaxMem
                handle++;
                simMem[handle] = nowSizeOfMem;
                sizeMem[handle] = nowSizeOfMem;
                cout << handle << endl;
            } else {
                nowSizeOfMem -= size; //如果超过了，退回刚才步骤
                cout << "NULL" << endl;
            }
        } else if (cmd == "del") {
            int delHandle;
            cin >> delHandle;
            // 如果 simMem[delHandel]（模拟的句柄编号的位置）是-1（被删除）或者是0（还没到Handel位置），那么是非法操作
            if(simMem[delHandle] != -1 && simMem[delHandle] != 0) {
                simMem[delHandle] = -1; //-1表示该Handel被删除
            } else {
                cout << "ILLEGAL_OPERATION" << endl;
            }
        } else if (cmd == "def") {
            for (int j = 0; j < sizeof(simMem)/sizeof(simMem[0]); j++){
                if (simMem[j] == -1){
                    nowSizeOfMem -= sizeMem[j];
                }
            }
        }
    }

    return 0;
}