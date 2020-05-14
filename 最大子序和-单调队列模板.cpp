/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-11 22:39:00
 */
#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 30
#define INF 0x3f3f3f3f
#define MAXF 2010
int n, m, r, c, s;
int sx, sy;
int cal[MAX] = {0};
int sum[MAX] = {0};

ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

deque<int> que;

int main()
{

    fcin >> n >> m;
   // int sum = 0;
    int maxn = 0x80000000;
    que.push_back(0);
    for (int i = 1; i <= n;i++){
       fcin >> cal[i];
        sum[i] =sum[i-1]+ cal[i];
        while(!que.empty()&&que.front()<i-m)
            que.pop_front(); 
        maxn = max(maxn, sum[i] - sum[que.front()]);
        while(!que.empty()&&sum[i]<sum[que.back()])//队头永远是当前i-m范围内，sum最小的一个，因为加入新值之前，所有大于新值的都弹出了
            que.pop_back();
        que.push_back(i);
    }
    fcout << maxn;

    fcin.close();
    fcout.close();

        return 0;
}