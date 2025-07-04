class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n));
        int max_len = 1, max_pos = 0;
        for (int i = 0; i < n; i++) {
            dp[i][0] = 1;
        }
        for (int len = 1; len < n; len++) {
            for (int i = 0; i < n - len; i++) {
                if (len == 1 && s[i] == s[i + 1]) {
                    dp[i][len] = 1;
                    if (len + 1 > max_len) {
                        max_len = len + 1;
                        max_pos = i;
                    }
                }
                else if (len > 1 && dp[i + 1][len - 2] > 0 && s[i] == s[i + len]) {
                    dp[i][len] = 1;
                    if (len + 1 > max_len) {
                        max_len = len + 1;
                        max_pos = i;
                    }
                }
            }
        }
        return s.substr(max_pos, max_len);
    }
};

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

// 马拉车
class Solution {
public:
    string longestPalindrome(string s) {
        std::string s1("$#");
        for (char& c : s) {
            s1 += c;
            s1 += "#";
        }
        int mid = 0, max_r = 0, ans_p = 0, ans_l = 1, len = s1.length();
        std::vector<int> p(2 * len + 3, 0);
        for (int i = 1; i < len; i++) {
            if (max_r >= i) {
                p[i] = std::min(p[(mid << 1) - i], max_r - i);
            }
            while (s1[i + p[i] + 1] == s1[i - p[i] - 1]) {
                p[i]++;
            }
            if (i + p[i] > max_r) {
                max_r = i + p[i];
                mid = i;
            }
            if (p[i] > ans_l) {
                ans_l = p[i];
                ans_p = (i - p[i]) >> 1;
            }
        }
        std::string ans = s.substr(ans_p, ans_l);
        return ans;
    }
};