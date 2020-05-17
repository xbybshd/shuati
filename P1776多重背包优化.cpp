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
#define MAX 1000005
#define INF 0x3f3f3f3f
#define MAXF 40020
int n, m, r, c, s;
int sx, sy;
int val[MAX] = {0};
int weigh[MAX] = {0};
int dpp[MAXF] = {0};
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);
int cnt = 0;


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
    fcin >> n >> m;
    for (int i = 1; i <= n;i++){
        int va, weg, cau;
        fcin >> va >> weg >> cau;
        int nj;
        for (nj = 1; nj < cau;nj<<=1){//二进制优化，cnt为全局物品数量，
            val[++cnt] = nj * va;
            weigh[cnt] = nj * weg;
            cau -= nj;
        }
        if(cau){//剩余没有剪完的
            val[++cnt] = cau * va;
            weigh[cnt] = cau * weg;
        }
    }
    int maxval = 0;
    for (int i = 1; i <= cnt;i++){
        for (int j = m; j >= weigh[i];j--){//一般的01背包
            dpp[j] = max(dpp[j], dpp[j - weigh[i]] + val[i]);
            if(i==cnt){
                maxval = max(maxval, dpp[j]);
            }
        }
    }
    fcout << maxval;

    fcin.close();
    fcout.close();

        return 0;
}