#include<cstdio>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<cstring>
#define db double
#define CLR(x) memset(x,0,sizeof(x))
using namespace std;
const db eps=1e-5;
db a[5];
int vis[5];
int dfs(int step)
{
    if(step==1){
        if(fabs(a[0]-24)<eps)
            return 1;
        else return 0;
    }
    for(int i=0;i<step-1;i++){
        for(int j=i+1;j<step;j++){
            db x=a[i];
            db y=a[j];
            a[j]=a[step-1];
            a[i]=x+y;

            if(dfs(step-1))
                return 1;

            a[i]=x-y;
            if(dfs(step-1))
                return 1;

            a[i]=y-x;
            if(dfs(step-1))
                return 1;

            a[i]=y*x;
            if(dfs(step-1))
                return 1;

            a[i]=x/y;
            if(dfs(step-1))
                return 1;


            a[i]=y/x;
            if(dfs(step-1))
                return 1;

            a[i]=x;
            a[j]=y;
        }
    }
    return 0;
}
int main()
{
    while(~scanf("%lf%lf%lf%lf",&a[0],&a[1],&a[2],&a[3])){
        CLR(vis);
        //printf("%lf %lf %lf %lf\n", a[0], a[1], a[2], a[3]);
        if(a[1]==0||a[2]==0||a[3]==0||a[0]==0){
            break;
        }
        if(dfs(4)){
            printf("YES\n");
        }
        else
            printf("NO\n");
    }
}