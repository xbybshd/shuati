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

using inll = unsigned long long;
#define Mod 1000000000
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

const int max_n = 100;
struct node {
    int x;
    int s;
};
node pi[max_n];
int dp[max_n][max_n], n;
/*
    pi 维度为目标点的数量，x是坐标，需要排序，s是分数
    dp i j，按照二维dp处理，值是最大分数，当前位置为i，它是从j点跳到i时的最大分数
    为啥不能只dp i j？因为这样只能保证从i到j的跳跃距离，无法限制住前一个到j的距离小于j到i
    所以对于j之前的一次也要遍历，因为这个是一个递推关系，只要保证当前两跳符合距离递增条件，后面的慢慢可以推上去。
    所以固定 i ，j 之后还要推一遍k，但是k目前没有必要开三维，只需要在二维内扫一遍，保存最大值即可
    先固定j，i取j+1，k取j。然后i每次加1，在内部k从j开始往后递减，当满足距离小于 i-j时，才进行更新判断。
    对于dp[i][j]的初始值可以由dp[i-1][j]代替，因为这个是前一步已经更新的值，后面更新k时需要与这个相比较。
    0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
                  j->
                    i->
                <-k
*/

int main() {
    fcin >> n;
    for (int i = 1; i <= n; i++) {
        fcin >> pi[i].x >> pi[i].s;
    }
    sort(pi + 1, pi + 1 + n, [](node a, node b) { return a.x < b.x; });
    int ans = pi[1].s;
    for (int j = 1; j <= n; j++) {
        dp[j][j] = pi[j].s;
        for (int i = j + 1, now = j; i <= n; i++) {
            dp[i][j] = dp[i - 1][j] - pi[i - 1].s;
            while (now >= 1 && (pi[j].x - pi[now].x <= pi[i].x - pi[j].x)) {
                dp[i][j] = max(dp[i][j], dp[j][now--]);
            }
            dp[i][j] += pi[i].s;
            ans = max(ans, dp[i][j]);
        }
    }
    for (int j = n; j >= 1; j--) {
        dp[j][j] = pi[j].s;
        for (int i = j - 1, now = j; i >= 1; i--) {
            dp[i][j] = dp[i + 1][j] - pi[i + 1].s;
            while (now <= n && (pi[now].x - pi[j].x <= pi[j].x - pi[i].x)) {
                dp[i][j] = max(dp[i][j], dp[j][now++]);
            }
            dp[i][j] += pi[i].s;
            ans = max(ans, dp[i][j]);
        }
    }
    fcout << ans;
    fcin.close();
    fcout.close();

    return 0;
}