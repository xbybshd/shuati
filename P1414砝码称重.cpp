/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-09 20:40:58
 */
#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 22
#define INF 0x3f3f3f3f
#define MAXF 2010
int n, m, r, c, s;
int sx, sy;
int fmm[MAX] = {0};
int dp[MAXF] = {0};
int vis[MAX] = {0};
int maxn;
int maxans;

void dpf(){
    memset(dp, 0, sizeof(dp));
    int ans = 0;
    dp[0] = 1;
    for (int i = 0; i < n;i++){
        if(vis[i]){
            int ll = fmm[i];
            for (int j = maxn; j>=ll;j--){
                dp[j] = max(dp[j - ll], dp[j]);
            }
        }
    }
    for (int j = maxn; j>0;j--){
        ans += dp[j];
    }
    maxans = max(ans, maxans);
}


void dfs(int ni,int nv){
    vis[ni] = 1;
    if(nv==r){
        dpf();
        vis[ni] = 0;
        return;
    }
    for (int i = ni + 1; i < m+1+nv;i++){
        dfs(i, nv + 1);
    }
    vis[ni] = 0;
}


 

int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);

    fcin >> n >> m;
    for (int i = 0; i < n;i++){
        fcin >> fmm[i];
    }
    r = n - m;
    maxn = r * 100;
    for (int i = 0; i < m+1;i++){
        dfs(i, 1);
    }

    fcout << maxans;

    fcin.close();
    fcout.close();

        return 0;
}