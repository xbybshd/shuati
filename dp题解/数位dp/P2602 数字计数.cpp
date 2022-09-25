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
const int max_n = 20;
const int max_m = 20;
int n, k;
ll a, b;
ll dp[max_n][max_m];
int elem[15];

ll dfs(int pos, bool limit, bool lead, ll sum, int dig) {
    ll ans = 0;
    if (pos == 0)
        return sum;
    if (!limit && lead && dp[pos][sum] != -1) // 先导零需要考虑，因为 0 xxx，1 xxx 算得的0的个数是不一样的
        return dp[pos][sum];
    int now = limit ? elem[pos] : 9;
    for (int i = 0; i <= now; i++) {
        ans += dfs(pos - 1, limit && (i == now), lead || i, sum + ((lead || i) && (i == dig)), dig);
    }
    if (!limit && lead)
        dp[pos][sum] = ans; // 状态 第一位肯定是位置，第二位是 sum 可以将各个数字按照状态sum分类，不同的 aaa xxx，bbb xxx，前三位sum是一样的话，后面因为xxx都是一样的，所以也是一样的；
    return ans;
}

ll solve(ll x, int dig) {
    ll res = 0;
    memset(elem, 0, sizeof(elem));
    memset(dp, -1, sizeof(dp));
    int ei = 0;
    while (x) {
        elem[++ei] = x % 10;
        x /= 10;
    }
    return dfs(ei, 1, 0, 0, dig);
}

int main() {
    fcin >> a >> b;
    for (int i = 0; i < 10; i++) {
        ll res = solve(b, i) - solve(a - 1, i);
        fcout << res << " ";
    }

    fcin.close();
    fcout.close();

    return 0;
}