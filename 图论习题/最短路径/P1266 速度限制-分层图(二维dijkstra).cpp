#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 10007
#define INF 1e9
#define MAXF 10000
#define MAXN 1000
#define Mod 100003

int n, m, d, cnt, min_v;

struct edge {
    int u, v, l, lv, pre;
    edge() {};
};

struct node {
    double time;
    int id;
    int lv;
    bool operator<(const node& b) const { return time > b.time; }
    node() {};
    node(double time_, int id_, int lv_)
        : time(time_)
        , id(id_)
        , lv(lv_) {};
};

int head[MAX];
edge emm[MAXF];
int vis[MAX][MAXN];
double dist[MAX][MAXN];
node path[MAX][MAXN];

priority_queue<node> heap;

void add_e(int u, int v, int lv, int l) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].l = l;
    emm[cnt].lv = lv;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

void dijkstra(int s) {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= MAXN; j++) {
            dist[i][j] = INF;
        }
    }
    dist[0][70] = 0;
    vis[0][70] = 1;
    heap.push(node(0, 0, 70));
    while (!heap.empty()) {
        int now = heap.top().id;
        int lv = heap.top().lv;
        vis[now][lv] = 0;
        heap.pop();
        for (int i = head[now]; i; i = emm[i].pre) {
            int v = emm[i].lv == 0 ? lv : emm[i].lv;
            int to = emm[i].v;
            if (dist[to][v] > dist[now][lv] + (double)emm[i].l / (double)v) {
                dist[to][v] = dist[now][lv] + (double)emm[i].l / (double)v;
                path[to][v] = node(0.0, now, lv);
                if (vis[to][v]) {
                    continue;
                }
                vis[to][v] = 1;
                heap.push(node(dist[to][v], to, v));
            }
        }
    }
    min_v = 0;
    dist[d][0] = INF;
    for (int i = 1; i <= MAXN; i++) {
        if (dist[d][min_v] >= dist[d][i] && dist[d][i] != INF) {
            min_v = i;
        }
    }
}

void print(int id, int v, ostream& out) {
    if (id != 0) {
        print(path[id][v].id, path[id][v].lv, out);
        out << path[id][v].id << " ";
    }
    else {
        return;
    }
}

int main() {
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);
    fcin >> n >> m >> d;
    for (int i = 1; i <= m; i++) {
        int u, v, lv, l;
        fcin >> u >> v >> lv >> l;
        add_e(u, v, lv, l);
    }
    dijkstra(0);
    print(d, min_v, fcout);
    fcout << d;
    fcin.close();
    fcout.close();

    return 0;
}