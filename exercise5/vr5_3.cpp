//
// Created by cakeal on 2023/4/29.
//
#include "iostream"
using namespace std;

int arr[110];

int main(){
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int  n,m;
        cin >> n >> m;
        if(m>=n){
            cout << 100 << endl;
        }
        for (int j = 1; j <= n; ++j) { // 从1开始
            cin >> arr[j];
            //cout << arr[j] << " ";
        }
        //cout << endl;
        arr[n+1] = 101;
        int max = -1;
        for (int j = 1; j <= n-m+1 ; ++j) {
            int apple = arr[j+m] - arr[j-1] - 1;
            if (apple > max) max = apple;
        }
        if(max == -1) continue;
        cout << max << endl;
    }
}