#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 300006
#define INF 1e9
#define MAXF 600006
#define MAXN 1000
#define Mod 100003
#define ll long long

int n, m, q, cnt, len, second;

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
int dist[MAX];
int length[MAX];
int fa[MAX];

void add_e(int u, int v, int w) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

int find(int x) {
    if (x == fa[x])
        return x;
    return fa[x] = find(fa[x]);
}

void dfs(int idx, int pre) {
    dist[idx] = dist[pre] + 1;
    if (dist[idx] > len) {
        len = dist[idx];
        second = idx;
    }
    for (int i = head[idx]; i; i = emm[i].pre) {
        int to = emm[i].v;
        if (to == pre) {
            continue;
        }
        dfs(to, idx);
    }
}

int main() {
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);
    fcin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        fcin >> u >> v;
        add_e(u, v, 0);
        add_e(v, u, 0);
        int fu = find(u);
        int fv = find(v);
        if (fu != fv) {
            fa[fv] = fu;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (find(i) != i) {
            continue;
        }
        dfs(i, 0);
        len = 0;
        dfs(second, 0);
        length[i] = len - 1;
        len = second = 0;
    }
    for (int i = 1; i <= q; i++) {
        int query, x, y;
        fcin >> query;
        if (query == 1) {
            fcin >> x;
            int ans = length[find(x)];
            fcout << ans << endl;
        }
        else if (query == 2) {
            fcin >> x >> y;
            int fx = find(x);
            int fy = find(y);
            if (fx == fy)
                continue;
            int ans = max(max(length[fx], length[fy]), ((length[fx] + 1) / 2 + (length[fy] + 1) / 2 + 1));
            length[fx] = ans;
            fa[fy] = fx;
        }
    }

    fcin.close();
    fcout.close();

    return 0;
}