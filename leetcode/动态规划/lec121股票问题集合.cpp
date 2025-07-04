
#define INF 0xBf3f3f3f

#define MAX 100000
#define INF 0xBf3f3f3f

int maxProfit1(vector<int>& prices) { // leetcode 121 只买卖1次，背包容量只有1
    int dp[MAX][2] = { 0 };
    int n = prices.size();
    if (n == 0)
        return 0;
    for (int i = 0; i < n; i++) {
        if (i - 1 == -1) {
            dp[i][0] = 0;
            dp[i][1] = -prices[0];

            continue;
        }
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);

        dp[i][1] = max(dp[i - 1][1], -prices[i]);
    }
    return dp[n - 1][0];
}

int maxProfit(vector<int>& prices) {
    // 当前的最大利润，要么是从前一次到这次卖了，要么是前一次之前卖了，要么是前一次到这次不动，后两种情况合并成一个
    // 都是前一次的最大值。前一次卖了，取得是前一次位置得到的最高的负数买入价格，类似单调队列
    int buy = 0;
    int ans = 0;
    for (int i = 0; i < prices.size(); i++) {
        if (i == 0) {
            buy = -prices[0];
            continue;
        }
        ans = std::max(ans, buy + prices[i]);
        buy = std::max(buy, -prices[i]);
    }

    return ans;
}

int maxProfit2(vector<int>& prices) { // leetcode 122可以无限次买，相当于不设容量的背包
    // 0代表当前未持有股票状态，来自于前一个未持有，前一个持有卖出，
    // 1 代表当前持有，来自前一个持有不动，前一个未持有但买入，价格计算在前面的基础上
    int dp[MAX][2] = { 0 };
    int n = prices.size();
    if (n == 0)
        return 0;
    for (int i = 0; i < n; i++) {
        if (i - 1 == -1) {
            dp[i][0] = 0;
            dp[i][1] = -prices[0];

            continue;
        }
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);

        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
    }
    return dp[n - 1][0];
}

class Solution {
public:
#define MAX 100000
#define INF 0xBf3f3f3f
    int maxProfit(vector<int>& prices) { // leetcode 123 只能买2次，要加上购买次数维度
        int dp[MAX][3][2] = { 0 };
        int n = prices.size();
        if (n == 0)
            return 0;
        dp[0][1][0] = 0;
        dp[0][1][1] = INF;
        dp[0][2][0] = 0;
        dp[0][2][1] = INF;
        for (int i = 1; i <= n; i++) {
            for (int k = 2; k >= 1; k--) {
                dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + price[i - 1])
                    dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - price[i - 1])
            }
        }
    }
    return dp[n][2][0];
};

class Solution { // 无限次买，但是每次买有手续费
public:
#define MAX 100000
#define INF 0xBf3f3f3f
    int maxProfit(vector<int>& prices, int fee) {
        int dp[MAX][2] = { 0 };
        int n = prices.size();
        if (n == 0)
            return 0;
        for (int i = 0; i < n; i++) {
            if (i - 1 == -1) {
                dp[i][0] = 0;
                dp[i][1] = -prices[0] - fee;

                continue;
            }
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);

            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i] - fee);
        }
        return dp[n - 1][0];
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = -prices[0] - fee;
        for (int i = 1; i < n; i++) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i] - fee);
        }
        return dp[n - 1][0];
    }
};

// 冷冻期，类似跳跃游戏
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        std::vector<std::vector<int>> dp(n + 2, std::vector<int>(2, 0));
        dp[0][1] = -prices[0];
        dp[1][1] = -prices[0];
        for (int i = 0; i < n; i++) {
            dp[i + 2][0] = std::max(dp[i + 1][0], dp[i + 1][1] + prices[i]);
            dp[i + 2][1] = std::max(dp[i + 1][1], dp[i][0] - prices[i]);
        }
        return dp[n + 1][0];
    }
};

class Solution { // 188可以买k次
public:
    int dp[1002][100][2] = { 0 };
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        int ans = 0x80000000;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                if (i == 0) {
                    dp[i][j][1] = -prices[i];
                }
                else {
                    dp[i][j][1] = std::max(dp[i - 1][j][1], (j != 0 ? dp[i - 1][j - 1][0] : 0) - prices[i]);
                    dp[i][j][0] = std::max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
                }
                if (i == n - 1) {
                    ans = std::max(ans, dp[i][j][0]);
                }
            }
        }
        return ans;
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        std::vector<std::vector<int>> dp(n + 2, std::vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for (int i = 1; i < n; i++) {
            if (i == 1) {
                dp[1][0] = std::max(dp[0][0], dp[0][1] + prices[1]);
                dp[1][1] = std::max(dp[0][1], dp[0][0] - prices[1]);
            }
            else {
                dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
                dp[i][1] = std::max(dp[i - 1][1], dp[i - 2][0] - prices[i]);
            }
        }
        return dp[n - 1][0];
    }
};

起始状态：
dp[-1][k][0] = 0;
dp[-1][k][1] = INF; // 还没开始买的时候不可能持有股票，所以为负无穷

dp[i][k][0] 第i天，还可以购买k次，当天不持有股票
            dp[i][k][1] 第i天，还可以购买k次，当天持有股票
                dp[i][k][1] 表示的是在第i天，最多进行k次交易取得的最大利润。这个最多进行k次，这样dp[i - 1][k - 1][0] 表示的是最多进行了k -
        1次交易，加上一次买入 操作，就转移到了最多进行k次交易的第i天。这个k不能认为是还剩可交易的次数，而是当时可能进行的最大交易次数。

            k类似背包问题中的容量，最多选择k个物品，那么选择了k个物品的时候自然是从k -
        1个物品转移过来的，正常情况下，初始把k >
    0的全部设为 - INF 有意义的数值只能从k = 0开始增加。

    dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][0] + price[i]) //第i天还允许买k次，不持有股票，等于前一天不持有股票，不做动作，或者前一天\
卖了股票加上收益,的最大值，允许买股票次数都等于k的原因是，k只有前一天买了股票才会减1，卖股票不变化
    dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - price[i])