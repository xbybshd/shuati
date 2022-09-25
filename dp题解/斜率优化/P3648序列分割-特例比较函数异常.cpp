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
const int max_n = 100;
const int max_m = 200;
int n, k;
ll f[max_n], g[max_n], pre[max_m][max_n], sum[max_n], a[max_n];
int que[max_n];

auto Y = [](int x) -> ll {
    return g[x] - sum[x] * sum[x];
};

auto slope = [](int x, int y) -> double { //比较函数出现异常的情况
    if (sum[x] == sum[y])
        return Y(y) >= Y(x) ? 1e18 : -1e18;
    return (Y(y) - Y(x)) / (double)(sum[y] - sum[x]);
};

int main() {
    fcin >> n >> k;
    int l, r;
    for (int i = 1; i <= n; i++) {
        fcin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    for (int t = 1; t <= k; t++) {
        l = r = 1;
        for (int i = 1; i <= n; i++) {
            g[i] = f[i];
        }
        for (int i = 1; i <= n; i++) {
            while (l < r && slope(que[l], que[l + 1]) >= -sum[i]) {
                l++;
            }
            int j = que[l];
            f[i] = g[j] + sum[j] * (sum[i] - sum[j]);
            pre[t][i] = j;
            while (l < r && slope(que[r - 1], que[r]) <= slope(que[r], i)) {
                r--;
            }
            que[++r] = i;
        }
    }
    fcout << f[n] << "\n";
    for (int i = pre[k][n]; k; i = pre[--k][i]) {
        fcout << i << " ";
    }

    fcin.close();
    fcout.close();

    return 0;
}