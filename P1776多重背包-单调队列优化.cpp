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
#define MAX 200
#define INF 0x3f3f3f3f
#define MAXF 400
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

struct node{
    int value;
    int pos;
    node(){};
    node(int vv, int pp) : value(vv), pos(pp){};
};

deque<node> que;

int main()
{
    int ni = 1;
    fcin >> n >> m;
    int maxva = 0;
    for (int i = 1; i <= n;i++){
        int va, weg, cau;
        fcin >> va >> weg >> cau;
        // if(weg==0)
        //     maxva += cau * va;
        int limit = min(m / weg,cau);//从当前j状态开始向前可以达到的状态数，小于物品数量和总容量除以物品容量
       
        for (int j = 0; j < weg;j++){
            int maxk = (m - j) / weg;//有多少个与j同余的状态
             que.clear();
            for (int k = 0; k <= maxk;k++){//从最小的与j同余的状态开始，到最大为止
                int valk = dpp[k * weg + j] - k * va;

                while(!que.empty()&&(que.front().pos)<k-limit)//太远了，此为止已经远与最大状态数，从队头去除
                    que.pop_front();
                while(!que.empty()&&(que.back().value)<=valk)//如果队尾当前的大小小于当前状态，就出队，维持单调递减
                    que.pop_back();
                que.push_back(node(valk,k));//入队
                dpp[k * weg + j] = max(dpp[k * weg + j],(que.front().value) + k * va);//取最大，加上的a*v[i]其中a就等于当前k
                if(i==n)
                    maxva = max(dpp[k * weg + j], maxva);
            }
        }
    }
    fcout << maxva;

    fcin.close();
    fcout.close();

        return 0;
}