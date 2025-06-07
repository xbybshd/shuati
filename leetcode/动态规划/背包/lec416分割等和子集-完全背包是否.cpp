class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0, n = nums.size();
        for (int& elem : nums) {
            sum += elem;
        }
        if (sum % 2 != 0) {
            return false;
        }
        sum /= 2;
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(sum + 1, 0));
        dp[0][0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            int cost = nums[i];
            for (int j = 0; j <= sum; j++) {
                // 主要是要穿透1
                dp[i + 1][j] = std::max(j >= cost ? dp[i][j - cost] : 0, dp[i][j]);
            }
        }
        return dp[n][sum];
    }
};