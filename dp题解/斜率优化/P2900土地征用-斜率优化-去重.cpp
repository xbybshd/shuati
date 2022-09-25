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
const int max_n = 5e4 + 5;
const int max_m = 10009;
int n, m, l;
ll dp[max_n];
struct node {
    ll w;
    ll h;
    node() {};
    bool operator<(const node& b) const {
        return w > b.w || (w == b.w && h > b.h);
    }
};
/*
    上凸包，左边取最优，要证明决策单调性，四边形不等式
    https://pengrui.blog.luogu.org/solution-p2900
*/
node a[max_n];
int que[max_n];
auto slope = [](int x, int y) -> double {
    return (dp[y] - dp[x]) / (double(a[y + 1].w - a[x + 1].w));
};

int main() {
    fcin >> n;
    for (int i = 1; i <= n; i++) {
        fcin >> a[i].w >> a[i].h;
    }
    sort(a + 1, a + n + 1);
    int h = 1;
    for (int i = 1; i <= n; i++) {
        if (a[h].h < a[i].h) {
            a[++h] = a[i];
        }
    }
    int l, r;
    l = r = 1;
    for (int i = 1; i <= h; i++) {
        while (l < r && slope(que[l], que[l + 1]) >= -a[i].h) {
            l++;
        }
        int j = que[l];
        dp[i] = dp[j] + a[j + 1].w * a[i].h;
        while (l < r && slope(que[r - 1], que[r]) <= slope(que[r], i)) {
            r--;
        }
        que[++r] = i;
    }
    fcout << dp[h];

    fcin.close();
    fcout.close();

    return 0;
}