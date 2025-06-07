#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 10007
#define INF 1e18
#define MAXF 100007
#define Mod 100003

int n, m, cnt, b;

struct edge {
    int u, v, w, pre;
    edge() {};
};

struct node {
    int id, w;
    node() {};
    node(int id_, int w_)
        : id(id_)
        , w(w_) {};
    bool operator<(const node& b) const { return w > b.w; }
};

edge emm[MAXF];
int f[MAX] = { 0 };
int head[MAX] = { 0 };
long long dist[MAX] = { 0 };
int vis[MAX] = { 0 };

priority_queue<node> heap;

void add_e(int u, int v, int w) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

void dijkstra(int s, int max_value) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[1] = 0;
    memset(vis, 0, sizeof(vis));
    heap.push(node(s, dist[s]));
    while (!heap.empty()) {
        int top = heap.top().id;
        heap.pop();
        if (vis[top]) {
            continue;
        }
        vis[top] = 1;
        for (int i = head[top]; i; i = emm[i].pre) {
            int to = emm[i].v;
            if (f[to] > max_value) {
                continue;
            }
            if (dist[to] > dist[top] + emm[i].w) {
                dist[to] = dist[top] + emm[i].w;
                if (!vis[to]) {
                    heap.push(node(to, dist[to]));
                }
            }
        }
    }
}

int main() {
    cin >> n >> m >> b;
    int l, r;
    l = r = 0;
    for (int i = 1; i <= n; i++) {
        cin >> f[i];
        r = max(r, f[i]);
    }
    l = max(f[1], f[n]);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_e(u, v, w);
        add_e(v, u, w);
    }
    while (l < r) {
        int mid = (l + r) >> 1;
        dijkstra(1, mid);
        if (dist[n] > b) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
    dijkstra(1, l);
    if (dist[n] > b) {
        cout << "AFK";
    }
    else {
        cout << l;
    }

    return 0;
}