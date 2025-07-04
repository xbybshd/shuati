
完全背包模板

class Solution {
public:
    int dp[9999];

    int coinChange(vector<int>& coins, int amount) {
        memset(dp, 0x3f, sizeof(dp)); //求最小所有的先初始化最大
        dp[0] = 0;
        int lens = coins.size();
        for (int i = 0; i < lens; i++) {
            int v = coins[i];
            for (int j = coins[i]; j <= amount; j++) {
                dp[j] = min(dp[j], dp[j - v] + 1);
            }
        }
        if (dp[amount] == 0x3f3f3f3f)
            return -1;
        else
            return dp[amount];
    }
};

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        std::vector<int> dp(amount + 1, 0x3f3f3f3f);
        dp[0] = 0;
        for (int i = 0; i < coins.size(); i++) {
            int cost = coins[i];
            for (int j = cost; j <= amount; j++) {
                dp[j] = std::min(dp[j], dp[j - cost] + 1);
            }
        }
        if (dp[amount] == 0x3f3f3f3f) {
            return -1;
        }
        else {
            return dp[amount];
        }
    }
};

// leetcode 518零钱兑换2 完全背包的背包方案数

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int coin_len = coins.size();
        std::vector<unsigned> dp(amount + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < coin_len; i++) {
            int cost = coins[i];
            for (int j = cost; j <= amount; j++) {
                dp[j] = dp[j] + dp[j - cost];
            }
        }
        return dp[amount];
    }
};

class Solution {
public:
    int dp[9999];
    int change(int amount, vector<int>& coins) {
        memset(dp, 0, sizeof(dp)); //求最小所有的先初始化最大
        dp[0] = 1; //起始设为0，其他为1
        int lens = coins.size();
        for (int i = 0; i < lens; i++) {
            int v = coins[i];
            for (int j = coins[i]; j <= amount; j++) {
                dp[j] = dp[j] + dp[j - v]; //转移方程设为加上
            }
        }
        if (dp[amount] == 0x3f3f3f3f)
            return -1;
        else
            return dp[amount];
    }
};