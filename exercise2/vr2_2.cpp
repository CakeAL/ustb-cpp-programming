//
// Created by cakeal on 2023/4/20.
//
#include <iostream>
#include <math.h>
using namespace std;

struct Location{
    int x;
    int y;
    int z;
    unsigned int travelTime;
}locations[100010];
int N;
int main(){
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> locations[i].x >> locations[i].y >> locations[i].z;
    }
    unsigned int minTravelTime = 0xFFFFFFFF;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            locations[i].travelTime += abs(locations[i].x - locations[j].x) +
                    abs(locations[i].y - locations[j].y) +
                    abs(locations[i].z - locations[j].z);
        }
        if(minTravelTime > locations[i].travelTime) {
            minTravelTime = locations[i].travelTime;
        }
    }
    cout << minTravelTime << endl;
    return 0;
}