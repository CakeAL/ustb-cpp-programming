#include <iostream>
using namespace std;

int main() {
    char str[16];
    cin >> str;
    short ans = 0;
    for (int i = 0; i < 16; i++){
        ans <<= 1;
        ans += str[i] - 48;
    }
    cout << ans << endl;
    return 0;
}
