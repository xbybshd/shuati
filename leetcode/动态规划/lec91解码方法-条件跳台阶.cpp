class Solution {
public:
    int numDecodings(string s) {
        int n = s.length();
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        // 为了方便计算dp[i-1]，整体dp下标从1开始，所以s要i-1
        for (int i = 1; i <= n; i++) {
            if (s[i - 1] != '0') { // 当前数不能为'0'，因为0无法转换为A-I的字符，如果可以转，那就相当于在到i-1的所有方案上加上一个字符
                dp[i] += dp[i - 1];
            }
            // 第二种是组成两个字符的情况，i-2不能有先导0，i-2，i和要小于等于26
            if (i > 1 && s[i - 2] != '0' && ((s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26)) {
                dp[i] += dp[i - 2];
            }
        }
        return dp[n];
    }
};