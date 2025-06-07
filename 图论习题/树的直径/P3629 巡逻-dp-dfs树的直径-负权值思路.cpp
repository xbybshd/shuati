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
int dp[MAX];
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
    if (flag == 1) // dfs求树的直径，保存路径节点每个都需要
        fa[idx] = pre;
    for (int i = head[idx]; i; i = emm[i].pre) {
        int to = emm[i].v;
        if (to != pre) {
            dfs(to, idx, flag);
        }
    }
}

void dfs_dp(int idx) { // dp树的直径模板
    vis[idx] = 1;
    for (int i = head[idx]; i; i = emm[i].pre) {
        int to = emm[i].v;
        if (vis[to] != 1) {
            dfs_dp(to);
            res = max(res, dp[idx] + emm[i].w + dp[to]);
            dp[idx] = max(dp[idx], dp[to] + emm[i].w);
        }
    }
}

void change(int idx) {
    while (fa[idx]) {
        int pre = fa[idx];
        for (int i = head[pre]; i; i = emm[i].pre) {
            int to = emm[i].v;
            if (to == idx) {
                emm[i].w = -1;
                break;
            }
        }
        for (int i = head[idx]; i; i = emm[i].pre) {
            int to = emm[i].v;
            if (to == pre) {
                emm[i].w = -1;
                break;
            }
        }
        idx = pre;
    }
}

int main() {
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);
    fcin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int u, v;
        fcin >> u >> v;
        add_e(u, v, 1);
        add_e(v, u, 1);
    }
    if (m == 1) {
        dfs(1, 0, 0);
        memset(dist, 0, sizeof(dist));
        len = 0;
        dfs(sec, 0, 0);
        int ans = 2 * n - len;
        fcout << ans << endl;
    }
    else {
        dfs(1, 0, 0);
        memset(dist, 0, sizeof(dist));
        len = 0;
        dfs(sec, 0, 1);
        int len1 = len;
        len = 0;
        change(sec);
        dfs_dp(1);
        int ans = 2 * n - len1 - res + 1;
        fcout << ans;
    }

    fcin.close();
    fcout.close();

    return 0;
}