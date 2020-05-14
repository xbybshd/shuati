#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
#define MAX 54
#define MAXN 0x3f3f3f3f
int g[MAX][MAX] = {0};
int dp[2*MAX][MAX][MAX] = {0};
int v[MAX]={0};
int w[MAX]={0};
int u[MAX] = {0};
int dp1[MAX]={0};
int dp2[MAX] = {0};
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
        for (int j = 1; j <= m;j++){
            cin >> g[i][j];
        }
    }
    int n2 =  n+m;
    for (int k = 3; k <n2;k++)//k是两个纸条横纵坐标之和
    for (int i =2; i <= (k>n?n:k);i++){//i是第一个纸条横坐标
        for (int j = 1; j <i;j++){//j是第二个，j不能超过i
            if(i!=j+1)
                {
                    dp[k][i][j] = max_ele(dp[k - 1][i - 1][j - 1], dp[k - 1][i - 1][j], dp[k - 1][i][j - 1], dp[k - 1][i][j]) + g[i][k - i] + g[j][k - j];
                }
            else{
                
                    dp[k][i][j] = max_ele(dp[k - 1][i - 1][j - 1], 0,dp[k - 1][i][j - 1], dp[k - 1][i][j]) + g[i][k - i] + g[j][k - j];
                
            }
        }
    }
    int aa=dp[n2 - 1][n][n-1];
    cout << dp[n2 - 1][n][n-1];

        return 0;

}
