//
// Created by cakeal on 2023/4/20.
//
#include <iostream>

using namespace std;

bool j(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    if(n == 1) {
        cout << "N" << endl;
        return 0;
    }
    if (j(n)) {
        cout << "Y" << endl;
    } else {
        cout << "N" << endl;
    }
    return 0;
}