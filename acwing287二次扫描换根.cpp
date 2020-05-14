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
#define MAX 601
#define INF 0x3f3f3f3f
#define MAXF 400
int n, m, r, c, s;
int sx, sy;
int val[MAX] = {0};
int head[MAX]={0};
int vis[MAX] = {0};
int dpp[MAX]= {0};
int fa[MAX]={0};
int ru[MAX] = {0};
int cnt=0;
int root = 1;
int maxans = 0;
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

struct edge{
    int to, pre,w;
    edge(){};
};

edge emu[MAX];

void add_e(int u,int v,int w){
    emu[++cnt].to=v;
    emu[cnt].pre=head[u];
    emu[cnt].w = w;
    head[u]=cnt;
}

void dfsdp(int ni){//dpp[i]为以1为起点，汇集到1时经过i点的流量
    vis[ni] = 1;//非树的深搜要有标记数组
    for (int i = head[ni]; i;i=emu[i].pre){
        int vi = emu[i].to;
        if(vis[vi]==1)
            continue;
        dfsdp(vi);
        if(ru[vi]==1)//后序
            dpp[ni] += emu[i].w;//入度为1说明是叶子结点，递归终点
        else
            dpp[ni] += min(emu[i].w, dpp[vi]);//为边ni，vi与经过vi流量的最小值
    }
}

void dfs(int ni){//利用汇聚到1的流量反推以ni为汇聚点的总流量
    vis[ni] = 0;
    for (int i = head[ni]; i;i=emu[i].pre){
        int vi = emu[i].to;
        if(vis[vi]==0)
            continue;
        if(ru[ni]==1)//先序
            fa[vi] = dpp[vi] + emu[i].w;
        else{
            fa[vi] = dpp[vi] + min((fa[ni] - min(dpp[vi], emu[i].w)), emu[i].w);
        }
        maxans = max(fa[vi], maxans);
        dfs(vi);
    
    }
}


int main()
{
    int ni = 1;
    int t;
    fcin >> t;
    while(t--){
        fcin >> n;
        for (int i = 0; i < n-1;i++){
            int u, v, w;
            fcin >> u >> v >> w;
            add_e(u, v, w);
            add_e(v, u, w);
            ru[v]++;
            ru[u]++;
        }
        dfsdp(1);
        fa[1] = dpp[1];
        maxans = fa[1];
        dfs(1);
        memset(dpp, 0, sizeof(dpp));
        memset(fa, 0, sizeof(fa));
        memset(ru, 0, sizeof(ru));
        memset(head, 0, sizeof(head));
        memset(emu, 0, sizeof(emu));
        cnt = 0;

        fcout << maxans << endl;
    }

    fcin.close();
    fcout.close();

        return 0;
}