#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 10020
#define INF 0x7fffffff
#define MAXF 500020
int n, m, r, c, s;
int sx, sy;
int u, v;
int fa[MAX] = {0};
int rk[MAX] = {0};
int cnt = 0;
int ans = 0;

int head[MAX] = {0};
int dist[MAX] = {0};
int vis[MAX] = {0};
int cycle[MAX]={0};


int find_b(int x){
    while(x!=fa[x])
        x = fa[x] = fa[fa[x]];
    return x;
}

struct edge{
    int u, v, w, pre;
    edge(){};

};

edge emm[MAXF];


void add_e(int u,int v,int w){
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

struct node{
    int w, now;//堆储存的节点是由到now号节点的距离w，和now节点的名称组成
    node(){};
    node(int ww, int nown) : w(ww), now(nown){};
    bool operator <(const node& b)const{
        return w > b.w;//优先队列是大根堆，大的在上面，重载小于号变成大于号
    }
};
priority_queue<node> qund;

priority_queue<int, vector<int>, greater<int> > xiaoq;//小顶堆 less函数 

void dijkstra(){
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;//起始点的距离设为0
    qund.push((node){0, s});//push起始点
    while(!qund.empty()){//每轮循环找出可以到达距离的最短点，然后将最短点可以到达的点加入堆
        node uu = qund.top();//取出可以到达的最短点
        qund.pop();//出堆
        int now = uu.now;
        if(vis[now]==1)
            continue;//因为添加堆节点的时候只要长度要被更新就会添加，不管是否已经访问过，对应情况是已经访问过得节点距离可能会随着新节点加入而减小
        vis[now] = 1;//设为已经访问过
        for (int i = head[now]; i; i = emm[i].pre){
            int nv = emm[i].v;//遍历新添加的节点的相邻节点
            if(dist[nv]>dist[now]+emm[i].w){
                dist[nv] = dist[now] + emm[i].w;
                qund.push((node){dist[nv], nv}); //如果节点长度被更新，添加新的node节点，之前的未更新的不影响排序，而且会在遍历到的时候被跳
            }
        }
    }
}

queue<int> que;

void spfa(){
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;//起始点的距离设为0
    que.push(s);
    while(!que.empty()){
        int ue = que.front();
        que.pop();
        vis[ue] = 0;
        for (int i = head[ue]; i;i=emm[i].pre){
            int nv = emm[i].v;
            if(dist[nv]>dist[ue]+emm[i].w){
                dist[nv] = dist[ue] + emm[i].w;
                if(!vis[nv]){
                    que.push(nv);
                    vis[nv] = 1;
                    // cycle[nv]++;入队一次判断环标记加1，大于n时有环
                    // if(cycle[nv]>n){
                    //     return;
                    // }
                }
            }

        }
    }
}

void spfa_d(int a){
    vis[a] = 1;
    for (int i = head[a]; i; i = emm[i].pre){
            int nv = emm[i].v;
            if(dist[nv]>dist[a]+emm[i].w){
                dist[nv] = dist[a] + emm[i].w;
                if(!vis[nv]){
                    spfa_d(nv);
                    //vis[nv] = 1;
                }
                // else{
                //     return;判断负环
                // }
            }
    }
}


int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);

    fcin >> n >> m >> s;
    for (int i = 0; i < m;i++){
        int eu, ev, ew;
        fcin >> eu >> ev >> ew;
        add_e(eu, ev, ew);
    }
    // dijkstra();
    // spfa();
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;//起始点的距离设为0
    spfa_d(s);
    for (int i = 1; i <= n;i++){
        if(i!=1)
            fcout << " ";
        if(dist[i]==0x3f3f3f3f)
            fcout << INF;
        else
            fcout << dist[i];
    }

        fcin.close();
    fcout.close();

        return 0;
}