#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 100009
#define INF 1e9
#define MAXF 200009
#define MAXN 1000
#define Mod 100003

int n, m, l, cnt;

struct edge {
    int u, v, w, pre;
    edge() {};
};

struct node {
    int idx, dis;
    node(int idx_, int dis_)
        : idx(idx_)
        , dis(dis_) {};
    bool operator<(const node& b) const { return dis > b.dis; }
};

edge emm[MAXF];
int head[MAX];
int vis[MAX];
int dist[MAX];
int path_id[MAX];
int short_vis[MAX];
int path[MAXF];
int path_vis[MAXF];
int path_dis[MAXF];

void add_e(int u, int v, int w) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

priority_queue<node> heap;

void spfa(int s) {
    memset(vis, 0, sizeof(vis));
    queue<int> que;
    vis[s] = 1;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        vis[u] = 0;
        que.pop();
        for (int i = head[u]; i; i = emm[i].pre) {
            int v = emm[i].v;
            if (!path_vis[i] && dist[v] > dist[u] + emm[i].w) {
                dist[v] = dist[u] + emm[i].w;
                if (path_id[v]) { // 路径上的点已经全部挖掉了，而且绕过最短路径只能有一次，回到最短路径点上就走不出去了，所以不经队
                    heap.push(node(path_id[v], dist[v] + path_dis[path_id[v]]));
                }
                else if (!vis[v]) {
                    vis[v] = 1;
                    que.push(v);
                }
            }
        }
    }
}

int main() {
    cin >> n >> m >> l;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_e(u, v, w);
    }
    for (int i = 1; i <= l; i++) {
        cin >> path[i]; // 最短边索引
        int v = emm[path[i]].v; // 第i条最短边的 v
        path_vis[path[i]] = 1; // 将最短边的
        path_id[v] = i + 1; // 路径上的每个点离散化
    }
    for (int i = l; i; i--) {
        path_dis[i] = path_dis[i + 1] + emm[path[i]].w;
    }
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    spfa(1);
    for (int i = 1; i <= l; i++) {
        while (!heap.empty() && heap.top().idx <= i)
            heap.pop();
        if (heap.empty()) {
            cout << "-1" << endl;
        }
        else {
            cout << heap.top().dis << endl;
        }
        dist[emm[path[i]].v] = dist[emm[path[i]].u] + emm[path[i]].w;
        spfa(emm[path[i]].v);
    }

    return 0;
}