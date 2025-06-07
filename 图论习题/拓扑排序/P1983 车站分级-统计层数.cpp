#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 300
#define INF 1e9
#define MAXF 300
#define MAXN 1000
#define Mod 100003
#define ll long long

int n, m, q, cnt, sec, res, jump, ans;
ll len;

int node[MAX];
int edge[MAX][MAX];
int input[MAX];
int stop[MAX];
int isstop[MAX];

void tpology_sort() {
    queue<pair<int, int>> que;
    ans = 1;
    for (int i = 1; i <= n; i++) {
        if (input[i] == 0) {
            que.push(make_pair(i, 1));
        }
    }
    while (!que.empty()) {
        auto u = que.front();
        int top = u.first;
        int floor = u.second;
        ans = max(floor, ans);
        que.pop();
        for (int i = 1; i <= n; i++) {
            if (edge[top][i]) {
                int to = i;
                input[to]--;
                if (input[to] == 0) {
                    que.push(make_pair(to, floor + 1)); // 最后减去的入度为0的边必然是长度最大的路径，所以不需要特殊处理
                }
            }
        }
    }
}

int main() {
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);
    fcin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a;
        fcin >> a;
        memset(stop, 0, sizeof(stop));
        memset(isstop, 0, sizeof(isstop));
        for (int i = 1; i <= a; i++) {
            fcin >> stop[i];
            isstop[stop[i]]++;
        }
        int beg = stop[1];
        int end = stop[a];
        for (int i = 1; i <= a; i++) {
            int u = stop[i];
            for (int i = beg; i <= end; i++) {
                if (!isstop[i] && !edge[u][i]) {
                    int v = i;
                    edge[u][v] = 1;
                    input[v]++;
                }
            }
        }
    }
    tpology_sort();
    fcout << ans;

    fcin.close();
    fcout.close();

    return 0;
}