#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 10005
#define INF 1e9
#define MAXF 1000000
#define MAXN 1000
#define Mod 100003
#define ll long long

int n, m, q, cnt, seq, part, ans;

struct edge {
    int u, v, w, pre;
    edge() {};
};

// tarjan
int head[MAX];
edge emm[MAXF];
int num[MAX];
int low[MAX];
int vis[MAX];

// 强连通分量归并和权重
int sd[MAX];
int wd[MAX];

int output[MAX];
int input[MAX];

stack<int> st;

void add_e(int u, int v, int w) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

void tarjan(int u) {
    num[u] = low[u] = ++seq;
    vis[u] = 1;
    st.push(u);
    for (int i = head[u]; i; i = emm[i].pre) {
        int to = emm[i].v;
        if (!num[to]) { // 未被dfs遍历到的点
            tarjan(to);
            low[u] = min(low[u], low[to]);
        }
        else if (vis[to]) { // 已经被dfs遍历到，而且在栈中的，即本连通分量之前遍历到的
            low[u] = min(low[u], low[to]); // 强连通分量可以变成num 对结果不影响，最上层因为会被low[to]的结果替代
        }
    }
    if (num[u] == low[u]) {
        int y;
        while (1) {
            y = st.top();
            st.pop();
            vis[y] = 0; // 是否入栈判断
            sd[y] = u; // 强连通分量标记
            if (u == y) { // low和num相同时说明已经到达强连通分量根节点
                break;
            }
            wd[u] += wd[y]; // 根节点的权重就不需要再加一次，所以在break后面
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int u;
        while (cin >> u && u != 0) {
            add_e(i, u, 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        wd[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        if (!num[i]) {
            tarjan(i);
        }
    }
    for (int i = 1; i <= cnt; i++) {
        int u = sd[emm[i].u];
        int v = sd[emm[i].v];
        if (u != v) {
            input[v]++;
            output[u]++;
        }
    }

    int zero_in, zero_out;
    zero_in = zero_out = 0;
    int num_scc = 0;
    for (int i = 1; i <= n; i++) {
        if (sd[i] == i) {
            num_scc++;
            if (input[i] == 0) {
                zero_in++;
            }
            if (output[i] == 0) {
                zero_out++;
            }
        }
    }
    ans = max(zero_in, zero_out);
    if (num_scc == 1) {
        ans = 0;
    }
    cout << zero_in << "\n"
         << ans;

    return 0;
}