#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 110005
#define INF 1e9
#define MAXF 2500001
#define MAXN 1000
#define Mod 100003

int n, m, k, s, t, cnt;

int head[MAX];

struct edge {
    int u, v, w, pre;
    edge() {};
};

struct node {
    int idx;
    int dis;
    node() {};
    node(int idx_, int dis_)
        : idx(idx_)
        , dis(dis_) {};
    bool operator<(const node& b) const { return dis > b.dis; }
};

edge emm[MAX * 6 + 8];

void add_e(int u, int v, int w) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

int vis[MAX];
int dist[MAX];

std::priority_queue<node> heap;

void dijstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    heap.push(node(s, 0));
    while (!heap.empty()) {
        node a = heap.top();
        heap.pop();
        int u = a.idx;
        if (vis[u]) {
            continue;
        }
        vis[u] = 1;
        for (int i = head[u]; i; i = emm[i].pre) {
            int to = emm[i].v;
            if (dist[to] > dist[u] + emm[i].w) {
                dist[to] = dist[u] + emm[i].w;
                heap.push(node(to, dist[to]));
            }
        }
    }
}

int main() {
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);
    fcin >> n >> m >> k;
    fcin >> s >> t;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        fcin >> u >> v >> w;
        add_e(u, v, w);
        add_e(v, u, w);
        for (int j = 1; j <= k; j++) {
            add_e(u + (j - 1) * n, v + j * n, 0);
            add_e(v + (j - 1) * n, u + j * n, 0);
            add_e(u + j * n, v + j * n, w);
            add_e(v + j * n, u + j * n, w);
        }
    }
    dijstra(s);
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= k; i++) {
        ans = min(ans, dist[t + i * n]);
    }
    fcout << ans;

    fcin.close();
    fcout.close();

    return 0;
}