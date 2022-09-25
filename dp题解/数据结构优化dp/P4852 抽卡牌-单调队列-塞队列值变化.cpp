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
const int max_n = 500;
const int max_m = 10009;
int n, m, c, d;
int a[max_n], sum[max_n], dp[max_n][max_m][2];
/*
    dp[i][j] = max(dp[i][j],dp[k][j-1]+a[k+1]+sum[i]-sum[k+c])
    i-c-d<=k<=i-c
    塞进队列的值，并不是循环的下标，而是要处理计算
*/
deque<int> que;

int calc(int pj, int pk) {
    return dp[pk][pj - 1][0] + a[pk + 1] - sum[pk + c];
}
inline void print(int i, int j, ostream& out) {

    if (!j)
        return;
    print(dp[i][j][1], j - 1, out);
    out << dp[i][j][1] + 1 << " ";
}

int main() {
    fcin >> n >> m >> c >> d;
    int all = c * n + m;
    for (int i = 1; i <= all; i++) {
        fcin >> a[i];
        sum[i] = a[i] + sum[i - 1];
    }
    memset(dp, 0xcf, sizeof(dp));
    for (int i = 1; i <= d; i++) {
        dp[i][0][0] = sum[i];
    }
    for (int j = 1; j <= n; j++) {
        int k;
        que.clear();
        for (k = max(0, c * j - c - d); k <= j * c - c; k++) {
            while (!que.empty() && calc(j, que.back()) <= calc(j, k)) {
                que.pop_back();
            }
            que.push_back(k);
        }
        for (int i = c * j; i <= all; i++, k++) {
            while (!que.empty() && que.front() < max(0, i - c - d)) {
                que.pop_front();
            }
            dp[i][j][0] = calc(j, que.front()) + sum[i];
            dp[i][j][1] = que.front();
            while (!que.empty() && calc(j, que.back()) <= calc(j, k)) {
                que.pop_back();
            }
            que.push_back(k);
        }
    }
    fcout << dp[all][n][0] << endl;
    print(all, n, fcout);
    fcin.close();
    fcout.close();

    return 0;
}