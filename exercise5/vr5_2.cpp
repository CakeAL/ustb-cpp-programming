//
// Created by cakeal on 2023/4/23.
//
#include "iostream"
using namespace std;

int map[110][110];
int sign[110][110];

void search(int x, int y){
    if(x-1 > 0 && y-1 > 0){

    }
}

int main(){
    int n, m;
    cin >> n >> m;
    int start_x,start_y;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> map[i][j];
            if(map[i][j] == '@'){
                start_x = j;
                start_y = i;
            }
        }
    }
    search(start_x, start_y);

    return 0;
}