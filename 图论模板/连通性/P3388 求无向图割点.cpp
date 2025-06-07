#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 20005
#define INF 200006
#define MAXF 200006
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
int cut[MAX];
stack<int> st;

void add_e(int u, int v, int w) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

void tarjan(int u, int pre) {
    num[u] = low[u] = ++seq;
    int child = 0;
    for (int i = head[u]; i; i = emm[i].pre) {
        int to = emm[i].v;
        if (!num[to]) { // 未被dfs遍历到的点
            tarjan(to, u);
            low[u] = min(low[u], low[to]);
            if (low[to] >= num[u] && u != pre) { // 只要有一个子节点的low数组满足，当前父节点就是割点
                cut[u] = 1;
            }
            if (u == pre) { // 只有在根节点特判子树数量
                child++;
            }
        }
        low[u] = min(low[u], num[to]); // 统计割点应该是low[v]
    }
    if (u == pre && child == 2) {
        cut[u] = 1;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_e(u, v, 1);
        add_e(v, u, 1);
    }
    for (int i = 1; i <= n; i++) {
        if (!num[i]) {
            tarjan(i, i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (cut[i] == 1) {
            ans++;
        }
    }
    cout << ans << endl;
    for (int i = 1; i <= n; i++) { //dfs内部统计割点会算重复，所以在外面统计
        if (cut[i] == 1) {
            cout << i << " ";
        }
    }

    return 0;
}