class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.length(), m = p.length();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= m; i++) {
            if (p[i - 1] == '*') { // 防止p位"**************"字符串
                dp[0][i] = 1;
            }
            else {
                break;
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
                    // 这里dp[i-1][j]的原因在于如果1-j包含*可以与1-i的某个字串匹配，那么会与1-i以及之后所有的匹配。
                    // 最开始是1-i0与1-j-1不包含*完全匹配，因为循环是先算i短的，此时对应下面的一般匹配
                    // 等到1-i0和1-j包含*那就转到dp[i][j-1],再下一轮1-i0+1过程中，就是利用dp[i-1][j];
                }
                else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        return dp[n][m];
    }
};