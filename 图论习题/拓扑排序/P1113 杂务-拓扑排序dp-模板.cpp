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
int input[MAX];
int weight[MAX];
int dp[MAX];

void add_e(int u, int v, int w) {
    emm[++cnt].u = u;
    emm[cnt].v = v;
    emm[cnt].w = w;
    emm[cnt].pre = head[u];
    head[u] = cnt;
}

void tpology_sort() {
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (input[i] == 0) {
            que.push(i);
        }
    }
    while (!que.empty()) {
        int top = que.front();
        que.pop();
        for (int i = head[top]; i; i = emm[i].pre) {
            int to = emm[i].v;
            dp[to] = max(dp[top] + weight[to], dp[to]);
            input[to]--;
            if (input[to] == 0) {
                que.push(to);
            }
        }
    }
}

int main() {
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);
    fcin >> n;
    for (int i = 1; i <= n; i++) {
        int u, v, w;
        fcin >> u >> w;
        weight[i] = w;
        dp[i] = w;
        while (fcin >> v && v != 0) {
            add_e(v, u, 1);
            input[u]++;
        }
    }
    tpology_sort();
    int ans = 0;
    for (int i = 1; i <= n; i++) { // 可能有多个点出度为0
        ans = max(ans, dp[i]);
    }
    fcout << ans;

    fcin.close();
    fcout.close();

    return 0;
}