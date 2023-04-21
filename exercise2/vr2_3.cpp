//
// Created by cakeal on 2023/4/20.
//
#include <iostream>
#include <algorithm>
using namespace std;

int A[10];

int cmp(int a, int b){
    return a > b;
}

int main(){
    unsigned int count = 0;
    for(int i = 0; i < 10; i++){
        cin >> *(A+i);
        if(*(A+i) == 0) count++;
    }
    sort(A, A+10, cmp);
    for(int i = 0; i < 10; i++){
        cout << *(A+i) << " ";
    }
    cout << endl << 10 - count << endl;
    return 0;
}