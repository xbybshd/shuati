/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include <bits/stdc++.h>
#include <queue>
#include <map>
#include <string>
// #include <iostream>
// #include <cstring>

using namespace std;
#define MAX 5009
#define INF 0x3f3f3f3f
#define MAXF 2003
#define P 19650827
#define M 100
int n, m, r, c, s;
int sx, sy;
int cnt = 0;
int root = 1;
int maxans = 0;
//typedef long long ll;
#define Mod 1000000007
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

int dpp[3][(1 << 10)][(1 << 10)] = {0}; //滚动数组，dpp[i][l][s]指的是当前行为i，上一行状态为l，当前行状态为s时，可以放多少个
int sum[(1 << 10)] = {0};               //每一行最多10个所以总状态不会超过1<<10;
int ac[105] = {0};
int getsum(int su)
{ //获得su中有多少个1，即炮兵数量
    int ni = 0;
    while (su)
    {
        if (su & 1)
            ni++;
        su >>= 1;
    }
    return ni;
}

int ff[MAX * 4] = {0};
int main()
{
    fcin >> n >> m;
    char x;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fcin >> x;
            ac[i] <<= 1;
            if (x == 'H')
                ac[i]++;
        }
    }
    int up = 1 << m;
    for (int i = 0; i < up; i++)
    {
        sum[i] = getsum(i); //把每种状态有多少个1算出来
    }
    for (int i = 0; i < up; i++)
    {
        if (!(i & ac[0] || (i & (i << 1)) || (i & (i << 2)))) //不能与高地冲突，不能与左边一格有冲突，不能与左边2格有冲突
        {
            dpp[0][0][i] = sum[i]; //第0行，当前状态为i，上一行为0
        }
    }
    for (int i = 0; i < up; i++)
    {
        for (int j = 0; j < up; j++)
        {
            if (!(i & ac[0] || j & ac[1] || i & j || (i & (i << 1)) || (i & (i << 2)) || (j & (j << 1)) || (j & (j << 2))))
                dpp[1][i][j] = sum[i] + sum[j]; //第1行，当前状态为j，上一行状态为i；
        }
    }
    for (int i = 2; i < n; i++)
    {
        for (int j = 0; j < up; j++)
        {
            if ((j & ac[i - 1] || (j & (j << 1)) || (j & (j << 2))))
                continue;
            for (int k = 0; k < up; k++)
            {
                if ((k & j || k & ac[i] || (k & (k << 1)) || (k & (k << 2))))
                    continue;
                for (int u = 0; u < up; u++)
                {
                    if ((u & j || u & k || u & ac[i - 2] || (u & (u << 1)) || (u & (u << 2))))
                        continue;
                    dpp[i % 3][j][k] = max(dpp[i % 3][j][k], dpp[(i - 1) % 3][u][j] + sum[k]);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < up; i++)
    {
        for (int j = 0; j < up; j++)
        {
            ans = max(ans, dpp[(n - 1) % 3][i][j]);
        }
    }
    fcout << ans;

    fcin.close();
    fcout.close();

    return 0;
}