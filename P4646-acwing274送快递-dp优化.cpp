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
#define MAX 303
#define INF 0x3f3f3f3f
#define MAXF 1010
int n, m, r, c, s;
int sx, sy;
int cala[MAX] = {0};
// int calb[MAX] = {0};
// int calc[MAX] = {0};
int dpp[2][MAX][MAX] = {0};
int gra[MAX][MAX] = {0};

ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);


// int max_t(int a,int b,int c){
//     int x = a > b ? a : b;
//     int y = x > c ? x : c;
//     return y;
// };

// void discrete(){
//     m = 1;
//     for (int i = 1; i <= n;i++){
//         if(i==1||calc[i]!=calc[i-1]){
//             calb[m++] = calc[i];
//         }
//     }
// }


int main()
{

    fcin >> n >> m;
    for (int i = 1; i <= n;i++){
        for (int j = 1; j <= n;j++){
            fcin >> gra[i][j];
        }
    }
    int minn = INF;
    memset(dpp, 0x3f, sizeof(dpp));
    dpp[0][1][2] = 0;
    cala[0] = 3;
    for (int i = 1; i <= m;i++){//dp[i][j][k],i代表第i个状态，其位置储存在cala数组里，不需要额外开一\
    维，j，k代表其他两个人位置
        fcin >> cala[i];
        int pi = cala[i];
        int pj=cala[i-1];
        int di = i & 1;
        int dj = (i - 1) &1;
        //memset(dpp[di], 0x3f, sizeof(dpp[di]));
        for (int j = 1; j < n;j++){
            for (int k = j+1; k <= n;k++){//涉及无向图矩阵的都可以优化一般
 if(j==k||j==pj||k==pj) continue;
                if(j!=pi&&k!=pi)
                dpp[di][j][k] = min(dpp[di][j][k], dpp[dj][j][k] + gra[pj][pi]);
                if(k!=pi&&pi!=pj){
                    int ul = pj < k ? pj : k;
                    int ur=pj > k ? pj : k;
                    dpp[di][ul][ur] = min(dpp[di][ul][ur], dpp[dj][j][k] + gra[j][pi]);
                }
                if(j!=pi&&pi!=pj){
                    int ul = pj < j ? pj : j;
                    int ur=pj > j ? pj : j;
                dpp[di][ul][ur] = min(dpp[di][ul][ur], dpp[dj][j][k] + gra[k][pi]);
                }
                dpp[dj][j][k]=INF;
}
        }
    }

    for (int i = 1;i<n;i++){
        for (int j = 1+i; j <= n;j++){
            minn = min(minn, dpp[m%2][i][j]);
        }
    }
    fcout << minn;

    fcin.close();
    fcout.close();

        return 0;
}