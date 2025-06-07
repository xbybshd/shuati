class Solution {
public:
    std::vector<std::string> res;
    int n;
    void dfs(int ni, std::string& s, std::vector<std::vector<std::string>>& ans, std::vector<std::vector<int>>& dp) {
        if (ni == n) {
            ans.emplace_back(res);
        }
        for (int i = ni; i < n; i++) {
            if (dp[ni][i]) {
                res.emplace_back(s.substr(ni, i - ni + 1));
                dfs(i + 1, s, ans, dp);
                res.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        n = s.length();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
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
            }
        }
        std::vector<std::vector<std::string>> ans;
        dfs(0, s, ans, dp);
        return ans;
    }
};