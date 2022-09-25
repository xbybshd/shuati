#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 100
#define INF 0x3f3f3f3f
#define MAXF 200
int n, m, r,c;
int sx, sy;
int u, v;
int fa[MAX] = {0};
int rk[MAX] = {0};
int cnt = 0;
int ans = 0;

int head[5020] = {0};
int dist[5020] = {0};
int vis[5020] = {0};

int find_b(int x){
    while(x!=fa[x])
        x = fa[x] = fa[fa[x]];
    return x;
}

struct edge{
    int v, w,pre;
    edge(){};
};

edge emm[MAXF << 1];

void add_e(int u,int v,int w){
    emm[++cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;

}

int Prim(){
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    int num_e = 0;
    
    int now = 1;
    for (int i = head[1]; i;i=emm[i].pre)
    {
        int ll = dist[emm[i].v];
        int vv = emm[i].v;
        int rr = emm[i].w;
        dist[emm[i].v] = min(dist[emm[i].v], emm[i].w);
    }
    while(++num_e<n){
        int min_e = INF;
        vis[now] = 1;//选中的点要做好标记
        for (int i = 1; i <=n;i++){//遍历所有没有加入集合的点，找出其从选出集合到未选集合距离最小的点，并不涉及距离更新
            if(!vis[i]&&min_e>dist[i]){
                now = i;
                min_e = dist[i];
            }
        }
        ans += min_e;
        for (int i = head[now]; i;i=emm[i].pre){
            int nv = emm[i].v;
            if(dist[nv]>emm[i].w&&!vis[nv]){//遍历已经选出的最小的点的所有邻边，如果终点属于未选集合，而且权值小于当前dist距离的话，更新dist
                dist[nv] = emm[i].w;
            }
        }
    }
    return ans;
}



int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);

    fcin >> n >> m;
    for (int i = 0; i < m;i++){
        int eu, ev, ew;
        fcin >> eu >> ev >> ew;
        add_e(eu, ev, ew);
        add_e(ev, eu, ew);
    }
    int res = Prim();
    fcout << res;

    fcin.close();
    fcout.close();

        return 0;
}