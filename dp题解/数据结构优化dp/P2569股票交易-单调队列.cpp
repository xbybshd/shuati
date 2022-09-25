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
int n, m, p, ap[max_n], bp[max_n], as[max_n], bs[max_n], dp[max_n][max_n];
deque<int> qa, qb;
/*
    i为天数，j为某天所持有的股票数，当前为j时，可以从四个方向进行转移
    1.直接从dp[0][0]转移，就是一直憋着不买也不卖，在这里买
    dp[i][j] = -j*ap[i];
    2.什么事情也不做，取前一天和今天最大值，这个意思是把最大值的行动i保留下来
    dp[i][j] = dp[i-1][j];
    3.有股票的时候再买入 k从小于j的部分转移来
    dp[i][j] = dp[i-w-1][k]-ap[i]*(j-k);   j-as[i]<=k<j;
    dp[i-w-1][k]+ap[i]*k     -ap[i]*j
    4。有股票的时候卖出，k从大于j的部分转移来
    dp[i][j] = dp[i-w-1][k]+bp[i]*(k-j);   j<k<=j+bs[i];
    dp[i-w-1][k]+bp[i]*k-bp[i]*j
*/
int main() {
    fcin >> n >> p >> m;
    for (int i = 1; i <= n; i++) {
        fcin >> ap[i] >> bp[i] >> as[i] >> bs[i];
    }
    memset(dp, 128, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= as[i]; j++) {
            dp[i][j] = -j * ap[i];
        }
        for (int j = 0; j <= p; j++) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
        if (i <= m) {
            continue;
        }
        qa.clear();
        qb.clear();
        for (int j = 0; j <= p; j++) {
            while (!qa.empty() && j - as[i] > qa.front()) {
                qa.pop_front();
            }
            while (!qa.empty() && dp[i - m - 1][qa.back()] + ap[i] * qa.back() <= dp[i - m - 1][j] + ap[i] * j) {
                qa.pop_back();
            }
            qa.push_back(j);
            dp[i][j] = max(dp[i][j], dp[i - m - 1][qa.front()] + ap[i] * qa.front() - ap[i] * j);
        }
        for (int j = p; j >= 0; j--) {
            while (!qb.empty() && j + bs[i] < qb.front()) {
                qb.pop_front();
            }
            while (!qb.empty() && dp[i - m - 1][qb.back()] + bp[i] * qb.back() <= dp[i - m - 1][j] + bp[i] * j) {
                qb.pop_back();
            }
            qb.push_back(j);
            dp[i][j] = max(dp[i][j], dp[i - m - 1][qb.front()] + bp[i] * qb.front() - bp[i] * j);
        }
    }
    int ans = 0;
    for (int j = 0; j <= p; j++) {
        ans = max(ans, dp[n][j]);
    }
    fcout << ans;

    fcin.close();
    fcout.close();

    return 0;
}