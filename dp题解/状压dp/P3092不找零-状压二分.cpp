/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 210

#define INF 0x5000000

using inll = unsigned long long;
#define Mod 1000000000
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);
#define N 1 << 17
#define MAXN 100006
int n, k, dp[N], f[N], coin[MAXN], pay[MAXN], sum[MAXN];
/*
    N 硬币状态的二次幂
    MAXN 最大物品数
    n 硬币数
    k 物品数
    dp 每个状态，最后能走到的最后面的物品下标
    f 每个状态，最后花的最少钱数，最开始会设为int最大值
    coin 硬币数组
    pay 物品价格数组
    sum 物品价格前缀和数组
    https://www.luogu.com.cn/blog/luckyblock/solution-p3092
    https://www.luogu.com.cn/blog/zhq316/solution-p3092
*/

// 二分最粗暴的写法
int split(int first, int last, int coin_val) {
    int l = first, r = last, mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (sum[mid] - sum[first - 1] == coin_val) {
            return mid;
        }
        if (sum[mid] - sum[first - 1] < coin_val) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return r; // 最粗暴的二分，在这里需要决定返回 l 还是 r，因为有可能 l 和 r 会错开
}

int main() {
    fcin >> n >> k;
    int total_money;
    int ans = 0x7fffffff;
    for (int i = 1; i <= n; i++) {
        fcin >> coin[i];
        total_money += coin[i];
    }
    for (int i = 1; i <= k; i++) {
        fcin >> pay[i];
        sum[i] = sum[i - 1] + pay[i];
    }
    int max_state = 1 << n;
    for (int i = 1; i < max_state; i++) { // 穷举每种状态
        for (int j = 0; j < n; j++) { // 每种状态下一次变化都只是变化一枚硬币，所以只要穷举每一枚硬币即可
            // 这里 i 代表当前状态，下面的逻辑是当前状态是由之前那些状态演变而来的，所以就是要从 i 的状态里面挖去一枚硬币
            if (i & (1 << j)) { // 遍历 i 有的硬币
                int last = (i ^ (1 << j)); // 把这枚硬币挖掉之后的状态，也就是前一个状态
                int sum_buy = split(dp[last] + 1, k, coin[j + 1]); // 前一个状态所走到的最后物品下标加1，和挖掉的硬币
                // 用着两个参数算出，前一个状态和加上的这枚硬币，可以往后走多远
                if (sum_buy > dp[i]) { // 如果跑的比现在还远，因为 i 可能由其他状态演变而来，所以之前也可能算过
                    dp[i] = sum_buy;
                    f[i] = f[last] + coin[j + 1];
                    if (dp[i] == k) { // 如果走到了最后
                        ans = min(ans, f[i]); // 更新总答案
                    }
                }
            }
        }
    }
    int res = total_money - ans;
    fcout << (((total_money - ans) < 0) ? -1 : res);

    fcin.close();
    fcout.close();

    return 0;
}