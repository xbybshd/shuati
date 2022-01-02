/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2021-12-20 00:02:38
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 210

#define INF 0x5000000

using inll = unsigned long long;
#define Mod 1000000000
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);
#define N 1 << 21
#define MAXN 100009
int n, m, que[MAXN], each_num[21], sum[MAXN][21], dp[N];
/*
    n 队伍的长度
    m 团体数量
    que 队伍的每个位置是那个团体
    each_num 每个团体有多少人
    sum 队伍从1开始，长度为len时，团体j有多少人
    dp 每一种状态，状态的维度是队伍的数量，每一位状态为1时，需要出列的人数

    https://www.luogu.com.cn/problem/solution/P3694

    本题最后求最少出列的人数，本质上是求一个排列方式：
    222244449999966666333333
    这种方式匹配到原来的输入排列后，如果不一样就要出列
    所以可以从最左边开始选择，每次是要把哪一类团体放到前面，如0010就是有0000放第二个最前面转移而来
    对于人数的计算，因为前面的已经匹配完，现在只看当前需要匹配的那一段长度，原始与匹配类有多少个重合
    dp[i] = min(dp[i], dp[i ^ (1 << (j - 1))] + each_num[j] - (sum[len][j] - sum[len - each_num[j]][j]));
*/

int main() {
    fcin >> n >> m;
    for (int i = 1; i <= n; i++) {
        fcin >> que[i];
        each_num[que[i]]++; // 统计每一类有多少人
        for (int j = 1; j <= m; j++) {
            sum[i][j] = sum[i - 1][j]; //计算当前长度i时，每一类有多少人
        }
        sum[i][que[i]]++;
    }
    int max_state = 1 << m;
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i < max_state; i++) {
        int len = 0;
        for (int j = 1; j <= m; j++) {
            if (i & (1 << (j - 1))) {
                len += each_num[j]; //当前状态为i时，所有i位数为1对应的状态加起来的总长度
            }
        }
        for (int j = 1; j <= m; j++) { //遍历每一个可以转移到当前状态的状态
            if (i & (1 << (j - 1))) { //如果是在i这个状态内部，就挖掉一块单独处理
                dp[i] = min(dp[i], dp[i ^ (1 << (j - 1))] + each_num[j] - (sum[len][j] - sum[len - each_num[j]][j]));
                //当前状态的最小错配人数，等于前一个状态的人数，加上需要转移的团队总人数，减去在[len - each_num[j],len]范围内，\
                j状态的人数,因为如果这个范围内是j就不需要匹配
            }
        }
    }
    fcout << dp[max_state - 1];

    fcin.close();
    fcout.close();

    return 0;
}