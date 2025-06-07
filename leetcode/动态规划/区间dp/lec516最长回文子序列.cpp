class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= n; i++) {
            dp[i][i] = 1;
            for (int j = i - 1; j >= 1; j--) {
                // 这两个最大值是相等的
                dp[i][j] = s[i - 1] == s[j - 1] ? dp[i - 1][j + 1] + 2 : std::max(dp[i - 1][j], dp[i][j + 1]);
            }
        }
        return dp[n][1];
    }
};

// i------>
// <-----ji