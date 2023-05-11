//
// Created by cakeal on 2023/4/23.
//
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
char map[40][40];
int dir[4][2]= {{1,0},{0,1},{0,-1},{-1,0}}; //走的方向
int sum=1;
int row,col;
struct node
{
    int x,y;
} start;  //start为起点
queue<node> a;
void bfs()
{
    node tmp1,tmp2;
    a.push(start);
    while(!a.empty())
    {
        tmp1=a.front();
        a.pop();
        for(int i=0; i<4; i++) //4个方向搜索 满足条件的插入队尾
        {
            tmp2.x=tmp1.x+dir[i][0];
            tmp2.y=tmp1.y+dir[i][1];
            if(tmp2.x>=0&&tmp2.x<row&&tmp2.y>=0&&tmp2.y<col&&map[tmp2.x][tmp2.y]=='.')
            {
                sum++;
                map[tmp2.x][tmp2.y]='#';   //对搜索到的黑瓷砖进行标记
                a.push(tmp2);
            }
        }
    }
}
int main()
{
    cin>>col>>row;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            cin>>map[i][j];
            if (map[i][j]=='@')
            {
                start.x=i;
                start.y=j;
            }
        }
    }
    bfs();
    cout<<sum<<endl;
}
