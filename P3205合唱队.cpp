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
int cal[MAX] = {0};
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

int dpp[MAX][MAX][3] = {0};


int main()
{
    fcin >> n;
    for (int i = 1; i <= n;i++){
        fcin >> cal[i];
    }
    for (int len = 2; len <= n;len++){
        int ri = n - len + 1;
        for (int i = 1; i <= ri;i++){
            if(len==2){
                if(cal[i]<cal[i+1]){
                    dpp[i][i + 1][0] = 2;
                    dpp[i][i + 1][1] = 1;
                    dpp[i][i + 1][2] = 1;
                }
                else{
                    dpp[i][i + 1][0] = 0;
                }
            }
            else{
                int j = i + len - 1;
                dpp[i][j][1] =(dpp[i][j][1]+ ((cal[i] < cal[i + 1]) ? dpp[i + 1][j][1] : 0))%P;
                dpp[i][j][1] =(dpp[i][j][1]+ ((cal[i] < cal[j]) ? dpp[i + 1][j][2] : 0))%P;
                dpp[i][j][2] =(dpp[i][j][2]+ ((cal[j] > cal[i]) ? dpp[i][j-1][1] : 0))%P;
                dpp[i][j][2] = (dpp[i][j][2]+((cal[j] > cal[j-1]) ? dpp[i][j-1][2] : 0))%P;
            }
        }
    }
    int ans = (dpp[1][n][1] + dpp[1][n][2]) % P;
    fcout << ans;

    fcin.close();
    fcout.close();

        return 0;
}