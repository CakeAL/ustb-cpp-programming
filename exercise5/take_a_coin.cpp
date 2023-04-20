// 将n枚硬币摆成环状，A和B轮流拿，A先拿。每个人拿的时候只可以选择拿走一个或者拿走相邻的两个，谁拿完最后的硬币胜利。
// 给定n <= 1000，并且假设双方都采取最优策略，输出最后的获胜者

// Created by 25910 on 2023/4/20.

// 看硬币排成1行 n=1,2 A赢 n=3 B赢， n=4 A赢，n=5 A赢
#include <iostream>
using namespace std;
const int maxn=1e3+5;
int n;
bool a_win[1005];
void init(int n){
    a_win[1]=a_win[2]= true;
    a_win[3]= false;
    for(int i=4;i<=n;i++){
        a_win[i]= (a_win[i - 1] || a_win[i - 2]);
    }

}
int main() {

    cin>>n;
    init(n);
    if(a_win[n-1]||a_win[n-2])cout<<'B';
    else cout<<'A';
    return 0;
}