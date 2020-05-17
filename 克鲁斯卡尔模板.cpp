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
    int u, v, w;
    edge(){};
    edge(int uu, int vv, int ww) : u(uu), v(vv), w(ww){};
    bool operator <(edge& b){
        return w < b.w;
    }
};

edge emm[MAXF << 1];

int Kruskal(){
    sort(emm, emm + m);
    for (int i = 0; i < m;i++){
        int eu = find_b(emm[i].u);
        int ev = find_b(emm[i].v);
        if(eu==ev){
            continue;
        }
        ans += emm[i].w;
        fa[eu]=ev;
        cnt++;
        if(cnt==n-1){
            break;
        }
    }
    return ans;
}



int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);

    fcin >> n >> m;
    for (int i = 0; i <=n;i++){
        fa[i] = i;
    }
        for (int i = 0; i < m; i++)
        {
            int eu, ev, ew;
            fcin >> eu >> ev >> ew;
            emm[i] = edge(eu, ev, ew);
        }
    int res =Kruskal ();
    fcout << res;

    fcin.close();
    fcout.close();

        return 0;
}