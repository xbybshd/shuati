/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2021-12-25 01:36:36
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 210

#define INF 0x5000000

using ll = long long;
#define Mod 1000000000
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);
const int max_n = 509;
const int max_m = 10009;
ll n, m, k, e;
ll dp[max_n][max_m];
struct node {
    ll x;
    ll f;
    ll c;
    node() {};
    node(ll xx, ll ff, ll cc)
        : x(xx)
        , f(ff)
        , c(cc) {}
};
node a[max_n];
deque<int> que;

//dp[i][j] = dp[i - 1][k] + a[i].c * (j - k) + (a[i].x - a[i - 1].x) * j * j;
int main() {
    fcin >> m >> e >> n;
    memset(dp, 0x3f, sizeof(dp));//找最小，初始化最大
    for (int i = 1; i <= n; i++) {
        ll x, f, c;
        fcin >> x >> f >> c;
        a[i] = node(x, f, c);
    }
    a[n + 1] = node(e, 0, 0);
    sort(a + 1, a + n + 1, [](node x, node y) { return x.x < y.x; });
    ll inf = dp[1][1];
    dp[0][0] = 0;//i = 0 这一行是没有实际意义的
    for (int i = 1; i <= n + 1; i++) {
        que.clear();
        dp[i][0] = 0;
        for (int j = 0; j <= m; j++) {
            while (!que.empty() && j - que.front() > a[i - 1].f) {
                que.pop_front();
            }
            if (dp[i - 1][j] != inf) {// 按照推理，i = 1时，所有的j都有dp[0][0]转移而来，所以不是无限大的状态才值得转移
                while (!que.empty() && dp[i - 1][que.back()] - que.back() * a[i - 1].c > dp[i - 1][j] - j * a[i - 1].c) {
                    que.pop_back();
                }
                que.push_back(j);
            }
            if (!que.empty())
                dp[i][j] = dp[i - 1][que.front()] + a[i - 1].c * (j - que.front()) + (a[i].x - a[i - 1].x) * j * j;
        }
    }
    fcout << dp[n + 1][m];
    printf("%lld", dp[n + 1][m]);

    fcin.close();
    fcout.close();

    return 0;
}