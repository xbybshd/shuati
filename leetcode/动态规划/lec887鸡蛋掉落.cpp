
// 状态为 (k,ni) = n ,鸡蛋数量，尝试数量，最后数值达到n即可
class Solution {
public:
    int superEggDrop(int k, int n) {
        if (n == 1) {
            return 1;
        }
        std::vector<int> dp(k + 1, 1);
        dp[0] = 0;
        int ans = -1;
        for (int i = 2; i <= n; i++) {
            for (int j = k; j >= 1; j--) {
                dp[j] = dp[j] + dp[j - 1] + 1;
            }
            if (dp[k] >= n) {
                ans = i;
                break;
            }
        }
        return ans;
    }
};

class Solution {
public:
    int superEggDrop(int k, int n) {
        if (n == 1) {
            return 1;
        }
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
        int ans = -1;
        for (int i = 1; i <= k; i++) {
            dp[1][i] = 1;
        }
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + 1;
            }
            if (dp[i][k] >= n) {
                ans = i;
                break;
            }
        }
        return ans;
    }
};

// 决策单调性
class Solution {
public:
    int superEggDrop(int k, int n) {
        if (n == 1) {
            return 1;
        }
        std::vector<std::vector<int>> dp(k + 1, std::vector<int>(n + 1, 0));
        for (int i = 0; i <= n; i++) { // 只有一个鸡蛋的时候，只能从上往下一层一层扔
            dp[1][i] = i;
        }
        for (int i = 2; i <= k; i++) {
            int x = 1;
            // 随着n的增加，真正的最小值的j是单调递增的，所以相当于x只遍历了一边
            for (int j = 1; j <= n; j++) {
                while (x < j && std::max(dp[i - 1][x - 1], dp[i][j - x]) > std::max(dp[i - 1][x], dp[i][j - x - 1])) {
                    x++;
                }
                dp[i][j] = std::max(dp[i - 1][x - 1], dp[i][j - x]) + 1;
            }
        }
        return dp[k][n];
    }
};