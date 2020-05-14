/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include<bits/stdc++.h>
#include <queue>
#include <map>
// #include <iostream>
// #include <cstring>

using namespace std;
#define MAX 83
#define INF 0x3f3f3f3f
#define MAXF 400
#define P 19650827
int n, m, r, c, s;
int sx, sy;
int cnt=0;
int root = 1;
int maxans = 0;
int pos[MAX] = {0};
int val[MAX] = {0};
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

int dpp[MAX][MAX][3] = {0};

int max_f(int a,int b,int c,int d){
    int x = a > b ? a : b;
    int y = x > c ? x : c;
    int z = y > d ? y : d;
    return z;
}

int main()
{
    fcin >> n >> m;
    int sumval = 0;
    for (int i = 1; i <= n;i++){
        fcin >> pos[i] >> val[i];
        sumval += val[i];
    }
    dpp[m][m][0] = 0;
    dpp[m][m][1] = 0;
    dpp[m][m][2] = sumval - val[m];
    for (int len = 2; len <= n;len++){
        int li = m - len + 1;
        int rj = m + len-1;
        for (int i = max(li,1); i <= m;i++){
            int j = i + len - 1;
            int leftl = dpp[i + 1][j][0] + dpp[i + 1][j][2] * (pos[i + 1] - pos[i]);
            int leftr = dpp[i + 1][j][1] + dpp[i + 1][j][2] * (pos[j] - pos[i]);

            int left = min(leftl, leftr);
            dpp[i][j][2] = dpp[i + 1][j][2] - val[i];
            if(j==rj){
                left= INF;
                dpp[i][j][2] = dpp[i][j-1][2] - val[j];
            }
            int right = min(dpp[i][j - 1][0] +dpp[i][j-1][2]*( pos[j] - pos[i]), dpp[i][j - 1][1] +dpp[i][j-1][2]*( pos[j] - pos[j-1]));
            if(i==li){
                right = INF;
                
                dpp[i][j][2] = dpp[i + 1][j][2] - val[i];
            }

            dpp[i][j][0] = left;
            dpp[i][j][1] = right;
        }
    }
    fcout << max(dpp[1][n][0], dpp[1][n][1]);
    fcin.close();
    fcout.close();

        return 0;
}