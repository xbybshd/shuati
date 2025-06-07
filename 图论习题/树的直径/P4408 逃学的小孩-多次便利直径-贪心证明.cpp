#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 300
#define INF 1e9
#define MAXF 300
#define MAXN 1000
#define Mod 100003
#define ll long long

int n, m, q, cnt, sec, res, jump;
ll len;

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
ll dist[MAX];
int fa[MAX];
ll da[MAX];
ll db[MAX];

void add_e(int u, int v, int w) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

void dfs(int idx, int pre, int edg, ll* dp) {
    dp[idx] = dp[pre] + edg;
    if (len < dp[idx]) {
        len = dp[idx];
        sec = idx;
    }
    for (int i = head[idx]; i; i = emm[i].pre) {
        int to = emm[i].v;
        int w = emm[i].w;
        if (to == pre) {
            continue;
        }
        dfs(to, idx, w, dp);
    }
}

int main() {
    // 贪心法的证明 https://www.luogu.com.cn/blog/ILikeDuck/solution-p4408
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);
    fcin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        fcin >> u >> v >> w;
        add_e(u, v, w);
        add_e(v, u, w);
    }
    dfs(1, 0, 0, dist);
    int first = sec;
    memset(dist, 0, sizeof(dist));
    len = 0;
    dfs(sec, 0, 0, da);
    ll la = len;
    dfs(sec, 0, 0, db);
    ll lb = 0;
    for (int i = 1; i <= n; i++) {
        ll res = min(da[i], db[i]);
        lb = max(lb, res);
    }
    ll ans = la + lb;
    fcout << ans;

    fcin.close();
    fcout.close();

    return 0;
}