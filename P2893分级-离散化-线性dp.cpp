/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include<bits/stdc++.h>
#include <queue>
#include <map>

using namespace std;
#define MAX 300
#define INF 0x3f3f3f3f
#define MAXF 2010
int n, m, r, c, s;
int sx, sy;
int cala[MAX] = {0};
int calb[MAX] = {0};
int calc[MAX] = {0};
int dpp[MAX][MAX] = {0};

ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);


int max_t(int a,int b,int c){
    int x = a > b ? a : b;
    int y = x > c ? x : c;
    return y;
};

void discrete(){
    m = 1;
    for (int i = 1; i <= n;i++){
        if(i==1||calc[i]!=calc[i-1]){
            calb[m++] = calc[i];//离散化模板
        }
    }
}


int main()
{

    fcin >> n;
    for (int i = 1; i <= n;i++){
        fcin >> cala[i];
        calc[i] = cala[i];
    }

    sort(calc + 1, calc + n + 1);
    discrete();
    m--;
    int ansup = INF;
    for (int i = 1; i <= n;i++){//第i个数且其等于第j大的B数组元素时的s值
        int minn = INF;
        for (int j = 1; j <=m;j++){
            minn = min(dpp[i - 1][j], minn);//将B数组离散化为第几大的数，每个ij有其上一行i且小于等于j的最小dp[i][j]转移而来
            dpp[i][j] = minn + abs(cala[i] - calb[j]);
            if(i==n)
                ansup = min(dpp[i][j], ansup);
        }
    }
    // int ansdown = INF;
    // for (int i = 1; i <= n;i++){
    //     int minn = INF;
    //     for (int j = m; j >=1;j++){
    //         minn = min(dpp[i - 1][j], minn);
    //         dpp[i][j] = minn + abs(cala[i] - calb[j]);
    //         if(i==n)
    //             ansdown = min(dpp[i][j], ansdown);
    //     }
    // }
    // int ans = ansup > ansdown ? ansdown : ansup;
    fcout <<ansup;
    fcin.close();
    fcout.close();

        return 0;
}