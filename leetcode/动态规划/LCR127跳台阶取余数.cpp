class Solution {
public:
    const int MOD = 1e9 + 7;
    int trainWays(int num) {
        int dp[101] = { 0 };
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= num; i++) {
            dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
        }
        return dp[num];
    }
};