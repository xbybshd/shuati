#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 300
#define INF 1e9
#define MAXF 300
#define MAXN 1000
#define Mod 100003
#define ll long long

int n, m, q, cnt, len, sec, res;

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
int vis[MAX];
int dist[MAX];
int deep[MAX];
int expect[MAX];
int ans[MAX];
int fa[MAX];

void add_e(int u, int v, int w) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

void dfs(int idx, int pre, int flag) {
    dist[idx] = dist[pre] + 1;
    if (len < dist[idx]) {
        len = dist[idx];
        sec = idx;
    }
    if (flag == 1) {
        fa[idx] = pre;
    }
    for (int i = head[idx]; i; i = emm[i].pre) {
        int to = emm[i].v;
        if (to == pre) {
            continue;
        }
        dfs(to, idx, flag);
    }
}

int dfs_m(int idx, int pre) {
    deep[idx] = deep[pre] + 1;
    int max_deep = deep[idx];
    for (int i = head[idx]; i; i = emm[i].pre) {
        int to = emm[i].v;
        if (to == pre) {
            continue;
        }
        max_deep = max(dfs_m(to, idx), max_deep);
    }
    expect[idx] = max_deep;
    return max_deep;
}

int main() {
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);
    fcin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        fcin >> u >> v;
        add_e(u, v, 1);
        add_e(v, u, 1);
    }
    dfs(1, 0, 0);
    memset(dist, 0, sizeof(dist));
    len = 0;
    dfs(sec, 0, 1);
    int mid = sec;
    for (int i = 1; i<(len + 1)>> 1; i++) {
        mid = fa[mid];
    }
    int a = dfs_m(mid, 0);
    for (int i = 1; i <= n; i++) {
        ans[i] = expect[i] - deep[i];
        // expect 为当前子节点下的子树所有子节点的最大深度，即当前子节点从根节点算长度时预期可以到达的最大深度
        // deep 为当前子节点的深度从当前节点算长度时达到的最大深度
    }
    sort(ans + 1, ans + n + 1, [](int a, int b) { return a > b; });
    int res = 0;
    for (int i = m + 1; i <= n; i++) {
        res = max(res, ans[i]);
    }
    fcout << res + 1;

    fcin.close();
    fcout.close();

    return 0;
}