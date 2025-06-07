#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 20006
#define INF 0x3f3f3f3f
#define MAXF 500010
#define Mod 100003

int n, m, cnt;

struct edge {
    int u, v, w, pre;
    edge() {};
};

int head[MAX] = { 0 };
long long dist[MAX] = { 0 };
int path[MAX] = { 0 };
int vis[MAX] = { 0 };

edge emm[MAX];

void add_e(int u, int v, int w) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

struct node {
    int w, now;
    node() {};
    node(int w_, int now_)
        : w(w_)
        , now(now_) {};
    bool operator<(const node& b) const { return w > b.w; }
};

priority_queue<node> heap;

void dijkstra(int s) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    memset(vis, 0, sizeof(vis));
    dist[s] = 0;
    heap.push(node(0, s));
    while (!heap.empty()) {
        node u = heap.top();
        heap.pop();
        int now = u.now;
        if (vis[now]) {
            continue;
        }
        vis[now] = 1;
        for (int i = head[now]; i; i = emm[i].pre) {
            int to = emm[i].v;
            if (dist[to] > dist[now] + emm[i].w) {
                dist[to] = dist[now] + emm[i].w;
                path[to] = path[now];
                if (!vis[to])
                    heap.push(node(dist[to], to));
            }
            else if (dist[to] == dist[now] + emm[i].w) {
                path[to] = (path[now] + path[to]) % Mod;
            }
        }
    }
}

int main() {
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);
    fcin >> n >> m;
    int u, v, w;
    for (int i = 0; i < m; i++) {
        fcin >> u >> v;
        add_e(u, v, 1);
        add_e(v, u, 1);
    }
    path[1] = 1;
    dist[1] = 0;
    dijkstra(1);
    for (int i = 1; i <= n; i++) {
        fcout << path[i] << endl;
    }

    fcin.close();
    fcout.close();

    return 0;
}