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
const int max_n = 1000;
const int max_m = 10009;
int n, m, l, a, b, c;
ll dp[max_n], val[max_n], sum[max_n];
int que[max_n];

auto Y = [](int x) -> ll {
    return dp[x] + a * sum[x] * sum[x] - b * sum[x];
};

auto slope = [](int x, int y) -> double {
    return (Y(y) - Y(x)) / (double)(sum[y] - sum[x]);
};

int main() {
    fcin >> n >> a >> b >> c;
    for (int i = 1; i <= n; i++) {
        fcin >> val[i];
        sum[i] += sum[i - 1] + val[i];
    }
    int l, r;
    l = r = 1;
    for (int i = 1; i <= n; i++) {
        // 按照规律，j,k,k更好，slope(j,k)=P(j)-P(k)  >  a,这个是上凸包
        while (l < r && slope(que[l], que[l + 1]) >= 2 * a * sum[i]) {
            l++; //直接取最左边的点的，应该证明四边形不等式
        }
        int j = que[l];
        dp[i] = dp[j] + a * (sum[i] - sum[j]) * (sum[i] - sum[j]) + b * (sum[i] - sum[j]) + c;
        while (l < r && slope(que[r - 1], que[r]) <= slope(que[r], i)) {
            r--;
        }
        que[++r] = i;
    }
    fcout << dp[n];

    fcin.close();
    fcout.close();

    return 0;
}