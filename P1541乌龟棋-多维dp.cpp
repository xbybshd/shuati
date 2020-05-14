#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
#define MAX 400
#define MAXN 121
//int g[MAX][MAX] = {0};
int dp[MAXN][MAXN][MAXN][MAXN] = {0};


int v[MAX]={0};
// int w[MAX]={0};
// int u[MAX] = {0};
// int dp1[MAX]={0};
// int dp2[MAX] = {0};
//int num[MAX] = {0};
int n, m;
int max_ele(int a,int b,int c,int d){
    if (b>a)
        a = b;
    if (c>a)
        a = c;
    if (d>a)
        a = d;
    return a;
}

int main()
{


    cin >> n >> m;
    for (int i = 1; i <= n;i++){
        cin >> v[i];
    }
    int su[5] = {0};
    for (int i = 0; i < m;i++){
        int mm;
        cin >> mm;
        su[mm]++;
    }
    int a = su[1];
    int b = su[2];
    int c = su[3];
    int d = su[4];
    dp[0][0][0][0] = v[1];
    for (int i = 0; i <=a;i++)
        for (int j = 0; j <= b;j++)
            for (int k = 0; k <= c;k++)
                for (int u = 0; u <= d;u++){
                    int num = i + j*2 + k*3 + u*4 + 1;
                    int maxe = 0;
                    if(i!=0)
                        dp[i][j][k][u] = max(dp[i][j][k][u], dp[i - 1][j][k][u] + v[num]);
                    if(j!=0)
                        dp[i][j][k][u] = max(dp[i][j][k][u], dp[i][j - 1][k][u] + v[num]);
                    if(k!=0)
                        dp[i][j][k][u] = max(dp[i][j][k][u], dp[i][j][k - 1][u] + v[num]);
                    if(u!=0)
                        dp[i][j][k][u] = max(dp[i][j][k][u], dp[i][j][k][u - 1] + v[num]);
                     
                }
    cout << dp[a][b][c][d];


        return 0;

}

