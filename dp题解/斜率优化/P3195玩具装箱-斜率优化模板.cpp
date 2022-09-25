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
ll a[max_n], sum[max_n], dp[max_n];
/*
   https://www.cnblogs.com/Xing-Ling/p/11210179.html

*/
ll que[max_n];
auto s = [](int x) -> ll {
    return sum[x] + x;
};
inline ll Y(int x) {
    return dp[x] + (s(x) + l + 1) * (s(x) + l + 1);
}
double slope(int x1, int x2) {
    return (Y(x2) - Y(x1)) / double(s(x2) - s(x1));
}

int main() {
    fcin >> n >> l;
    for (int i = 1; i <= n; i++) {
        fcin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    int head, tail;
    head = tail = 1; //正常队列起始是l=1.r=0；这里提前塞入j=0；
    for (int i = 1; i <= n; i++) {
        while (head < tail && (slope(que[head], que[head + 1]) <= 2 * s(i))) {
            head++;
        }
        int j = que[head];
        dp[i] = dp[j] + (s(i) - s(j) - 1 - l) * (s(i) - s(j) - 1 - l);
        while (head < tail && (slope(que[tail - 1], que[tail]) >= slope(que[tail], i))) {
            tail--;
        }
        que[++tail] = i;
    }
    fcout << dp[n];
    fcin.close();
    fcout.close();

    return 0;
}