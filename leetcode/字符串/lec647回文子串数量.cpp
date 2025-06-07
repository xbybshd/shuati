// dp暴力
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
        int ans = n;
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (j == i + 1) {
                    dp[i][j] = s[i] == s[j];
                }
                else {
                    dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
                }
                ans += dp[i][j];
            }
        }
        return ans;
    }
};