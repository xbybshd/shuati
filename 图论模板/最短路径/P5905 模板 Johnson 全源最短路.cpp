#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 10005
#define INF 1e9
#define MAXF 500010

int n, m, cnt;

struct edge {
    int u, v, w, pre;
    edge() {};
};

int head[MAX] = { 0 };
long long dist[MAX] = { 0 };
long long dist_sp[MAX] = { 0 };
int vis[MAX] = { 0 };
int vis_sp[MAX] = { 0 };
int cycle[MAX] = { 0 };

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
queue<int> que;

bool spfa(int s) {
    memset(dist_sp, 0x3f, sizeof(dist_sp));
    dist_sp[s] = 0;
    que.push(s);
    vis_sp[s] = 1;
    while (!que.empty()) {
        int ue = que.front();
        que.pop();
        vis_sp[ue] = 0;
        for (int i = head[ue]; i; i = emm[i].pre) {
            int nv = emm[i].v;
            if (dist_sp[nv] > dist_sp[ue] + emm[i].w) {
                dist_sp[nv] = dist_sp[ue] + emm[i].w;
                if (!vis_sp[nv]) {
                    que.push(nv);
                    vis_sp[nv] = 1;
                    cycle[nv]++;
                    if (cycle[nv] > n) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

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
                if (!vis[to])
                    heap.push(node(dist[to], to));
            }
        }
    }
}

int main() {

    cin >> n >> m;
    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        add_e(u, v, w);
    }
    for (int i = 1; i <= n; i++) {
        add_e(0, i, 0);
    }
    if (!spfa(0)) {
        cout << -1;
        return 0;
    }
    // https://www.luogu.com.cn/problem/solution/P5905
    // 虚拟节点然后过spfa的意义在于，是算出来虚拟节点连每个顶点的边的权值，都与原边满足三角形不等式
    for (int i = 1; i <= n; i++) {
        for (int u = head[i]; u; u = emm[u].pre) {
            emm[u].w += (dist_sp[i] - dist_sp[emm[u].v]);
        }
    }
    for (int i = 1; i <= n; i++) {
        dijkstra(i);
        long long ans = 0;
        for (int j = 1; j <= n; j++) {
            if (dist[j] == INF) {
                ans += j * INF;
            }
            else {
                ans += j * (dist[j] - (dist_sp[i] - dist_sp[j]));
            }
        }
        cout << ans << endl;
    }

    return 0;
}