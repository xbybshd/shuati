class Solution {
public:
    int numTrees(int n) {
        int dp[20] = { 0 };
        dp[1] = 1;
        dp[0] = 1; // 因为是乘法，所以是1
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i] += (dp[j - 1] * dp[i - j]);
            }
        }
        return dp[n];
    }
};