class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.length(), m = text2.length();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int left_up = dp[i - 1][j - 1] + (text1[i - 1] == text2[j - 1] ? 1 : 0);
                dp[i][j] = std::max(left_up, std::max(dp[i - 1][j], dp[i][j - 1]));
            }
        }
        return dp[n][m];
    }
};

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.size(), n2 = text2.size();
        int dp[1005][1005] = { 0 };
        int max_ans = 0;
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                int left = dp[i][j - 1];
                int up = dp[i - 1][j];
                int left_up = dp[i - 1][j - 1];
                left_up += text1[i - 1] == text2[j - 1] ? 1 : 0;
                dp[i][j] = std::max(left_up, std::max(left, up));
            }
        }
        int ans = dp[n1][n2];
        return ans;
    }
};

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.size(), n2 = text2.size();
        std::vector<std::vector<int>> dp(n1 + 1, std::vector<int>(n2 + 1));
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                int left_up = dp[i][j] + (text1[i] == text2[j] ? 1 : 0);
                dp[i + 1][j + 1] = std::max(left_up, std::max(dp[i][j + 1], dp[i + 1][j]));
            }
        }
        int ans = dp[n1][n2];
        return ans;
    }
};