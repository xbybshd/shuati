/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-11 03:44:06
 */
#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 5009
#define INF 0x3f3f3f3f
#define MAXF 2010
int n, m, r, c, s;
int sx, sy;
char ss1[MAX] = {0};
char ss2[MAX] = {0};

int dpp[2][MAX] = {0};
int fpp[2][MAX] = {0};

ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);


int max_t(int a,int b,int c){
    int x = a > b ? a : b;
    int y = x > c ? x : c;
    return y;
}

int main()
{

    fcin >> ss1 >> ss2;
    int l1 = strlen(ss1) - 1;
    int l2 = strlen(ss2) - 1;
    ss1[l1] = 0;
    ss2[l2] = 0;
    int now, pre;
    for(int i=0;i<=l2;i++){
        fpp[0][i] = 1;
    }
     fpp[1][0] = 1;//将两个数组第0位初始化为1
    for (int i = 1; i <= l1;i++){
        if(i%2==1){
            pre = 0;
            now = 1;
        }
        else{
            pre = 1;
            now = 0;
        }
       
        for (int j = 1; j <= l2;j++){
            //dpp[i][j] = max_t(dpp[i - 1][j], dpp[i][j - 1], dpp[i - 1][j - 1] + (ss1[i-1] == ss2[j-1]));
            
            dpp[now][j] = max_t(dpp[pre][j], dpp[now][j - 1], dpp[pre][j - 1] + (ss1[i - 1] == ss2[j - 1]));
            int lu = 0;
            int u = 0;
            int ln = 0;
            int lc = 0;
            fpp[now][j] = 0;
            if(dpp[pre][j]==dpp[now][j])
                ln = fpp[pre][j];
            if(dpp[now][j-1]==dpp[now][j])
                u =fpp[now][j - 1];
            if(ss1[i-1]==ss2[j-1]&&dpp[now][j]==dpp[pre][j-1]+1)//如果上左都不相等，必然为此项，要加上左上
                lu = fpp[pre][j - 1];
            if(dpp[pre][j-1]==dpp[now][j])//容斥原理，左上与右下相等必然加了两次，而且此种情况必然四个都相等
                lc= -(fpp[pre][j - 1]);
            fpp[now][j] = (lu + u + ln+lc)%100000000;
        }
    }
    fcout << dpp[now][l2]<<endl;
    fcout << fpp[now][l2];

    fcin.close();
    fcout.close();

        return 0;
}