class Solution {
public:
    int numDistinct(string s, string t) {
        typedef unsigned long long ull;
        int n = s.size(), m = t.size();
        std::vector<std::vector<ull>> dp(n + 1, std::vector<ull>(m + 1));
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == t[j - 1]) { // 相等的时候加上左上，否则加上，左上代表可以从前一个子序列字母转移到这里，上代表之前的一样的字母
                    // 收集总和
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][m];
    }
};

class Solution {
public:
    int numDistinct(string s, string t) {
        typedef unsigned long long ull;
        int n = s.size(), m = t.size();
        std::vector<ull> dp(m + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }
        return dp[m];
    }
};