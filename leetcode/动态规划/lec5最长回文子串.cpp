int dp[1001][1001] = { 0 };
std::string longestPalindrome(std::string s) {
    int max_pos = 0;
    int max_len = 1;
    for (int i = 0; i < s.length(); i++) {
        dp[i][0] = 1;
    }
    for (int j = 1; j < s.length(); j++) {
        for (int i = 0; i < s.length() - j; i++) {
            if (j == 1 && s[i] == s[i + j]) {
                dp[i][j] = 2;
                if (max_len < dp[i][j]) {
                    max_len = dp[i][j];
                    max_pos = i;
                }
            }
            else if (j > 1 && dp[i + 1][j - 2] > 0 && s[i] == s[i + j]) {
                dp[i][j] = dp[i + 1][j - 2] + 2;
                if (max_len < dp[i][j]) {
                    max_len = dp[i][j];
                    max_pos = i;
                }
            }
        }
    }
    std::string s1 = s.substr(max_pos, max_len);
    return s1;
}