//
// Created by cakeal on 2023/5/10.
//
#include <iostream>
using namespace std;
int arr[8][8];
int vis[8][8];
bool check()
{
    for (int i = 1; i < 5; i++)
        for (int j = 1; j < 7; j++)
            vis[i + 1][j] = (arr[i][j] + vis[i][j - 1] + vis[i][j] + vis[i][j + 1] + vis[i - 1][j]) % 2;

    for (int i = 1; i < 7; i++)
    {
        if ((vis[5][i - 1] + vis[5][i] + vis[5][i + 1] + vis[4][i]) % 2 != arr[5][i])
            return false;
    }
    return true;
}

void sol()
{
    for (int i = 1; i < 7; i++)
        vis[1][i] = 0;
    while (!check())
    {
        vis[1][1]++;
        int tag = 1;
        while (vis[1][tag] > 1)
        {
            vis[1][tag] = 0;
            tag++;
            vis[1][tag]++;
        }
    }
}

int main()
{
    int round;
    cin >> round;
    for (int k = 0; k< round; k++)
    {
        cout<<"PUZZLE #"<<k+1<<endl;
        for (int i = 0; i < 6; i++)
        {
            vis[i][0] = vis[i][7] = 0;
        }
        for (int i = 0; i < 7; i++)
        {
            vis[0][i] = 0;
        }
        for (int i = 1; i < 6; i++)
        {
            for (int j = 1; j < 7; j++)
            {
                cin >> arr[i][j];
            }
        }
        sol();
        for (int i = 1; i < 6; i++)
        {
            for (int j = 1; j < 7; j++)
            {
                cout << vis[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}