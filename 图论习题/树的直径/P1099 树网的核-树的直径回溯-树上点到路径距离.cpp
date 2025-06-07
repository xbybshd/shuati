#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 300
#define INF 1e9
#define MAXF 300
#define MAXN 1000
#define Mod 100003
#define ll long long

int n, m, q, cnt, len, sec, res, jump;

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
int mark[MAX];
int head[MAX];
int dist[MAX];
int fa[MAX];

void add_e(int u, int v, int w) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

void dfs(int idx, int pre, int edg, int flag) {
    dist[idx] = dist[pre] + edg;
    if (len < dist[idx]) {
        len = dist[idx];
        sec = idx;
    }
    for (int i = head[idx]; i; i = emm[i].pre) {
        int to = emm[i].v;
        int w = emm[i].w;
        if (to == pre || mark[to]) { // mark为标记的直径点，在遍历时直接绕过可以达到切分点的效果
            continue;
        }
        if (flag == 1) {
            fa[to] = idx;
        }
        dfs(to, idx, w, flag);
    }
}

int main() {
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);
    fcin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        fcin >> u >> v >> w;
        add_e(u, v, w);
        add_e(v, u, w);
    }
    dfs(1, 0, 0, 0);
    int first = sec;
    memset(dist, 0, sizeof(dist));
    len = 0;
    dfs(sec, 0, 0, 1);
    int ans = 0x3f3f3f3f;
    for (int i = sec, j = sec; i; i = fa[i]) { // 双指针从直径的遍历终点往回回溯的模板
        while (dist[j] - dist[i] > m) {
            j = fa[j];
        }
        int x = max(dist[sec] - dist[j], dist[i]);
        ans = min(ans, x);
    }
    for (int i = sec; i; i = fa[i]) { // 把树的直径的每个边都去掉，让每个点孤立
        mark[i] = 1;
    }
    memset(dist, 0, sizeof(dist));
    for (int i = sec; i; i = fa[i]) { // 孤立直径上的点之后，对所有的直径点做为起点的dfs，相当于遍历了很多独立的树
        dfs(i, fa[i], 0, 0);
    }
    for (int i = 1; i <= n; i++) { // 在这些树中取距离最大的，因为存在一种情况，目标路径覆盖了整个直径，这个时候最远点只能在直径之外出
        ans = max(ans, dist[i]);
    }

    fcout << ans;

    fcin.close();
    fcout.close();

    return 0;
}