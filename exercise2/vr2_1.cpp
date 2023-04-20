//
// Created by cakeal on 2023/4/20.
//
#include <iostream>
#include <cstdio>
using namespace std;

char s[5000];
char subs[5000];

int main(){
    scanf("%s %s", s, subs);
    int count = 0;
    char *ch;
    ch = s;
    while(*ch != 0){
        if(*ch == *subs){
            char *mch = ch;
            char *chs = subs;
            while(*chs != 0){
                if(*mch != *chs){
                    count--;
                    break;
                }
                chs++;mch++;
            }
            count++;
        }
        ch++;
    }
    cout << count << endl;
    return 0;
}