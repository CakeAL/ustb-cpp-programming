//
// Created by cakeal on 2023/4/20.
//
#include <iostream>
//#include <algorithm>
using namespace std;

int a[10];

void move(int *arry, int n, int m){
    int temp[100];
    for(int i = 0; i < m; ++i){
        temp[i] = *(arry+(n-m)+i);
    }
    for(int i = n; i >= m; i--){
        *(arry+i) = *(arry+i-m);
    }
    for(int i = 0; i < m; ++i){
        *(arry+i) = temp[i];
    }
}

int main(){
    int n = 10, m = 3;
    for(int i = 0; i < n; i++){
        cin >> *(a+i);
    }
    move(a, n, m);
    for(int i = 0; i < n; i++){
        cout << *(a+i) << " ";
    }
    cout << endl;
    return 0;
}
