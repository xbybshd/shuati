int longestValidParentheses(string s) {
    int n = s.length();
    std::vector<int> dp(n + 1, 0);
    int max_ans = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {
                dp[i] = (i > 1 ? dp[i - 2] : 0) + 2;
            }
            else if (dp[i - 1] > 0) {
                if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(') {
                    dp[i] = dp[i - 1] + 2;
                    if (i - dp[i - 1] - 2 >= 0) {
                        dp[i] += dp[i - dp[i - 1] - 2];
                    }
                }
            }
        }
        max_ans = std::max(max_ans, dp[i]);
    }
    return max_ans;
}