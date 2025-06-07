class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
        dp[0][0] = 1; // 00是匹配的，因为这里要作为起点，保证 "","a*"这种也是0-0匹配的转移起点
        auto compare = [&](int i, int j) {
            if (i == 0) { // 正常情况下，s是空字符串，所有的p的匹配都失效
                return false;
            }
            if (p[j - 1] == '.') { // 下表i，j匹配的是s[i-1]p[j-1]，如果p[j-1]是'.'，那么就可以匹配任何一个字符
                return true;
            }
            return s[i - 1] == p[j - 1]; // 最后再比较真正的字符
        };

        for (int i = 0; i <= n; i++) {
            for (int j = 1; j <= m; j++) { // p为空字符也没有比较意义，但是i为空字符，会有a*这种匹配0个
                if (p[j - 1] == '*') {
                    dp[i][j] |= dp[i][j - 2]; //这里j-2可能默认*必然最低位置是第二个，出现a*,此时可以把a*完全扔掉，看s[0-i]p[0-j-2]的匹配
                    if (compare(i, j - 1)) { // 如果s[i] 与*前面的匹配，那么了理论上来说要看i-1,j-2是否匹配，但是a*这种实际上可以用多次
                        // 其中包含了s[i-1]p[j-2]的匹配情况 所以是s[i-1]p[j]
                        dp[i][j] |= dp[i - 1][j];
                    }
                }
                else {
                    if (compare(i, j)) { // 这个就单独看最后一个是否匹配
                        dp[i][j] |= dp[i - 1][j - 1];
                    }
                }
            }
        }
        return dp[n][m];
    }
};