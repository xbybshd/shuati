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
#define MAX 30
#define INF 0x3f3f3f3f
#define MAXF 900
int n, m, r, c, s;
int sx, sy;
int cald[MAX] = {0};
int calp[MAX] = {0};
int calld[MAX] = {0};
int callp[MAX] = {0};
int calsum[MAX] = {0};
int calred[MAX] = {0};

struct node{
    int red,p, d;
    node() { ;
        red= INF;
        p = 0;
        d = INF;
    }
    node(int pp,int dd):p(pp),d(dd){
        red =abs(pp-dd);
    }
};

int dpp[MAX][MAXF]={0};
int dpf[MAX][MAX][MAXF] = {0};
int ans[MAX] = {0};

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
    int ni = 1;
    while(fcin >> n >> m){
        if(n==0)
            break;
        for (int i = 1; i <= n;i++){
            int d, p;
            fcin >> p >> d;
            int red = abs(p - d);

            cald[i] =d;
            calp[i] = p;
            calsum[i] = d + p;
            calred[i] = red;
        }
        int limt_m = (m * 40 + 40);
        int addm = m * 20 + 5;
        int addl = m * 20 + 20;
        memset(dpp, -0x3f, sizeof(dpp));
        dpp[0][addl] = 0;
        for (int i = 1; i <= n;i++){//i是n个物品的背包循环
            //多维动态规划应该把最后考虑的放在数值上，越优先考虑的放在dp维度里，本题中，差值比和优先，差值一样的时候，对于和有最大的标准来比较\
            但是和相同的时候，再比较差值，与原题意的比较函数有冲突。
            for (int j = m; j > 0;j--){//j是选m个物品的循环
                int prej = j - 1;
                for (int k =addm; k>=-addm;k--){//k是sum（p[i]-d[i]) 直接用p-d代表绝对值，有可能为负值，所以最后搜索是从0开始向两边搜索
                    if(dpp[j-1][k-(calp[i]-cald[i])+addl]>=0&&dpp[j-1][k-(calp[i]-cald[i])+addl]+calp[i]+cald[i]>dpp[j][k+addl]){
                        dpp[j][k + addl] = dpp[j - 1][k - (calp[i] - cald[i]) + addl] + calp[i] + cald[i]; //dpp的值是前i个物品里取m个当sum(p-d)为k时\
                        sum(p+d)的最大值
                        dpf[i][j][k + addl] = 1;//取1代表当前用了第i个物品，回溯的时候要减去（p[i]-d[i])
                    }//要有负值的下标的话，应该加上偏移值，
                    else{
                        dpf[i][j][k + addl] = 0;
                    }
                    
            }
        }
        }
        int min_red=0;
        int min_i = 0;
        for (int k = 0; k <= addm;k++){
            if(min_red<dpp[m][k+addl]){
                min_red = dpp[m][k + addl];
                min_i = k;
            }
            if(min_red<dpp[m][-k+addl]){
                min_red = dpp[m][-k + addl];
                min_i = -k;
            }
            if(min_red>0){
                break;
            }
        }
            int ansi = m;
        int lastm=m;
        int lastk = min_i;
        int ans[22];
        int last_p = 0;
        int last_d = 0;
        for (int i = n; i >= 1;i--){
            if(dpf[i][lastm][lastk+addl]==0)
                continue;
            else{
                lastm--;
                lastk -= (calp[i]-cald[i]);
                last_p += calp[i];
                last_d += cald[i];
                ans[ansi--] = i;
            }
        }
            fcout << "Jury #" << ni << "\n";
        fcout << "Best jury has value " <<  last_p << " for prosecution and value " <<  last_d << " for defence:\n";
        for (int i = 1; i <= m;i++)
        {
            fcout << " " << ans[i];
        }
        fcout << "\n\n";
            ni++;
    };


    fcin.close();
    fcout.close();

        return 0;
}