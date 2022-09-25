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
#define Mod 20130427
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);
const int max_n = 109;
const int max_m = 2;
int B, n, m;
int L[max_n], R[max_n];
ll a[max_n][2], len[max_n][2], suffix[max_n][2], q[max_n][2], sum[max_n];

ll solve(int* p, int l) {
    memset(a, 0, sizeof(a));
    memset(len, 0, sizeof(len));
    memset(suffix, 0, sizeof(suffix));
    memset(q, 0, sizeof(q));
    a[l][0] = 1;
    for (int i = l - 1; i >= 0; i--) {
        int c = (i == l - 1 ? 0 : B);
        a[i][0] = a[i + 1][0];
        a[i][1] = (c - 1 + a[i + 1][1] * B + a[i + 1][0] * p[i]) % Mod;
        len[i][0] = len[i + 1][0] + a[i + 1][0];
        len[i][1] = (c - 1 + (a[i + 1][1] + len[i + 1][1]) * B + len[i][0] * p[i]) % Mod;
        suffix[i][0] = (B * suffix[i + 1][0] + len[i][0] * p[i]) % Mod;
        suffix[i][1] = (sum[c] + (suffix[i + 1][1] * B % Mod * B + (len[i + 1][1] + a[i + 1][1]) * sum[B]) + B * suffix[i + 1][0] * p[i] + len[i][0] * sum[p[i]]) % Mod;
        q[i][0] = (q[i + 1][0] + suffix[i][0]) % Mod;
        q[i][1] = (q[i + 1][1] * B + q[i + 1][0] * p[i] + suffix[i][1]) % Mod;
    }
    return (q[0][0] + q[0][1]) % Mod;
}

int main() {
    fcin >> B;
    for (int i = 1; i <= B; i++) {
        sum[i] = (sum[i - 1] + i - 1) % Mod;
    }
    fcin >> n;
    for (int i = 0; i < n; i++) {
        fcin >> L[n - i - 1];
    }
    for (int i = 0; i < n; i++) {
        if (L[i] > 0) {
            L[i]--;
            break;
        }
        L[i] = B - 1;
    }
    if (!L[n - 1])
        n--;
    fcin >> m;
    for (int i = 0; i < m; i++) {
        fcin >> R[m - i - 1];
    }
    fcout << ((solve(R, m) - solve(L, n) + Mod) % Mod);

    fcin.close();
    fcout.close();

    return 0;
}