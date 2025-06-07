#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 300
#define INF 1e9
#define MAXF 300
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

// 拓扑排序
int hd[MAX];
edge emd[MAXF];
int input[MAX];
int output[MAX];
int dp[MAX];

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
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);
    fcin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        fcin >> u >> v;
        add_e(u, v, 1);
    }
    for (int i = 1; i <= n; i++) {
        wd[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        if (!num[i]) {
            tarjan(i);
        }
    }
    int zero_out = 0;
    int last = 0;
    for (int i = 1; i <= n; i++) {
        if (sd[i] == i && output[i] == 0) {
            last = i;
            zero_out++;
        }
    }
    if (zero_out != 1) { // 充分必要条件就是只有一个出度为0的点，多了少了都是无解
        fcout << 0;
        return 0;
    }
    fcout << wd[last];

    fcin.close();
    fcout.close();

    return 0;
}