#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 100008
#define INF 1e9
#define MAXF 500008
#define MAXN 1000
#define Mod 100003
#define ll long long

int t, n, m, k, cnt;

struct edge {
    int u, v, w, pre;
    edge() {}
};

struct node {
    int idx;
    ll dis;
    node(int idx_, ll dis_)
        : idx(idx_)
        , dis(dis_) {};
    bool operator<(const node& b) const { return dis > b.dis; }
};

edge emm[MAXF];
int head[MAX];
int candidate[MAX];

int vis[2][MAX];
ll dist[2][MAX];
int color[2][MAX];

int eu[MAXF];
int ev[MAXF];
int ew[MAXF];

void add_e(int u, int v, int w) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

void dijstra(int id) { // 方向，因为是起点为集合
    memset(dist[id], 0x3f, sizeof(dist[id]));
    memset(vis[id], 0, sizeof(vis[id]));
    priority_queue<node> heap;
    for (int i = 1; i <= k; i++) { //起始点是一个集合，只要把所有的集合点距离设为0，再全部塞入堆即可
        dist[id][candidate[i]] = 0;
        heap.push(node(candidate[i], 0));
        color[0][candidate[i]] = candidate[i];
        color[1][candidate[i]] = candidate[i];
    }
    while (!heap.empty()) {
        node a = heap.top();
        heap.pop();
        int u = a.idx;
        if (vis[id][u]) {
            continue;
        }
        vis[id][u] = 1;
        for (int i = head[u]; i; i = emm[i].pre) {
            int to = emm[i].v;
            if (dist[id][to] > dist[id][u] + emm[i].w) {
                dist[id][to] = dist[id][u] + emm[i].w;
                color[id][to] = color[id][u]; // 记录当前点的最短路径是从哪个起始点来的
                heap.push(node(to, dist[id][to]));
            }
        }
    }
}

void clear() {
    memset(head, 0, sizeof(head));
    memset(emm, 0, sizeof(emm));
    cnt = 0;
}

int main() {
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);

    fcin >> t;
    while (t--) {
        clear();
        fcin >> n >> m >> k;
        for (int i = 1; i <= m; i++) {
            fcin >> eu[i] >> ev[i] >> ew[i];
            add_e(eu[i], ev[i], ew[i]);
        }
        for (int i = 1; i <= k; i++) {
            fcin >> candidate[i];
        }
        dijstra(0);
        clear();
        for (int i = 1; i <= m; i++) { // 换所有边的方向再dijstra，求的是所有其他点到起点距离
            add_e(ev[i], eu[i], ew[i]);
        }
        dijstra(1);
        ll ans = 0x3f3f3f3f;
        for (int i = 1; i <= m; i++) {
            int u = eu[i];
            int v = ev[i];
            int w = ew[i];
            if (color[0][u] && color[1][v] && (color[0][u] != color[1][v])) { //
                ans = min(ans, dist[0][u] + dist[1][v] + w);
            }
        }
        fcout << ans << endl;
    }

    fcin.close();
    fcout.close();

    return 0;
}