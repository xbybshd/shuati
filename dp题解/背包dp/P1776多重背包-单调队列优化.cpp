/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include <bits/stdc++.h>
#include <map>
#include <queue>

// #include <iostream>
// #include <cstring>

using namespace std;
#define MAX 200
#define INF 0x3f3f3f3f
#define MAXF 400
int n, m, r, c, s;
int sx, sy;
int val[MAX] = { 0 };
int weigh[MAX] = { 0 };
int dpp[MAXF] = { 0 };
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);
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

struct node {
    int value;
    int pos;
    node() {};
    node(int vv, int pp)
        : value(vv)
        , pos(pp) {};
};

deque<node> que;

int main() {
    int ni = 1;
    fcin >> n >> m;
    int maxva = 0;
    for (int i = 1; i <= n; i++) {
        int va, weg, cau;
        fcin >> va >> weg >> cau;
        // if(weg==0)
        //     maxva += cau * va;
        int limit = min(m / weg, cau); //从当前j状态开始向前可以达到的状态数，小于物品数量和总容量除以物品容量

        for (int j = 0; j < weg; j++) { // j指的是余数，范围只能说0到第一个物品重量为止，多重是从前往后推
            int maxk = (m - j) / weg; //有多少个与j同余的状态，即从当前余数开始，理论上能往前推多少个k，没有算数量限制
            que.clear();
            for (int k = 0; k <= maxk; k++) { //从最小的与j同余的状态开始，到最大为止，k就是从余数开始，往后可以推得物品状态
                int valk = dpp[k * weg + j] - k * va; //推到的状态重量
                //在这里，虽然k可以到最大，但是k转移的原状态是有范围的，因为k转移的原状态与其他物品是公用的，虽然k往后推有限制\
                但是这个状态可以来自前面一些物品的记录，所以当得到转移前状态的时候，要判断是否超过最大物品数量。
                while (!que.empty() && (que.front().pos) < k - limit) //太远了，此为止已经远与最大状态数，从队头去除
                    que.pop_front();
                while (!que.empty() && (que.back().value) <= valk) //如果队尾当前的大小小于当前状态，就出队，维持单调递减
                    que.pop_back(); //这里，如果当前小于队尾，那就不管，把当前入队，在下面算一次比较。如果当前大于队尾，就把\
                    队尾出队，因为只要入队的节点，在下面都算了一次比较，所以出队无所谓。这个是要维持单调递减，不需要在比较的|\
                    的时候与每个队列元素都比较一次，只与队尾比较即可
                que.push_back(node(valk, k)); //入队
                dpp[k * weg + j] = max(dpp[k * weg + j], (que.front().value) + k * va); //取最大，加上的a*v[i]其中a就等于当前k
                if (i == n)
                    maxva = max(dpp[k * weg + j], maxva);
            }
        }
    }
    fcout << maxva;

    fcin.close();
    fcout.close();

    return 0;
}