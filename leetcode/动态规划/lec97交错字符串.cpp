class Solution {
public:
    std::vector<std::vector<int>> dp;
    bool dfs(int n1, int n2, string s1, string s2, string s3) {
        if (n1 < 0 && n2 < 0) {
            return true;
        }
        // n1和n2分别指代下标，而不是长度，但是会存在n1比较完了，但是n2依然还剩余的情况，此时n1=-1，只有当两边都是-1的时候才结束
        int& res = dp[n1 + 1][n2 + 1];
        if (res != -1) {
            return res;
        }
        // 当n1==0且匹配完全的时候，下一次进入的就是n1=-1，此时如果n2没有匹配完全，之后都是n1<0，n2大于等于0
        res = (n1 >= 0 && s1[n1] == s3[n1 + n2 + 1] && dfs(n1 - 1, n2, s1, s2, s3)) || (n2 >= 0 && s2[n2] == s3[n1 + n2 + 1] && dfs(n1, n2 - 1, s1, s2, s3));
        return res;
    }
    bool isInterleave(string s1, string s2, string s3) {
        int l1 = s1.length();
        int l2 = s2.length();
        int l3 = s3.length();
        dp = std::vector<std::vector<int>>(l1 + 1, std::vector<int>(l2 + 1, -1));
        if (l3 != l1 + l2) {
            return false;
        }
        return dfs(l1 - 1, l2 - 1, s1, s2, s3);
    }
};

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int l1 = s1.length();
        int l2 = s2.length();
        int l3 = s3.length();
        if (l1 + l2 != l3) {
            return false;
        }
        std::vector<std::vector<int>> dp(l1 + 1, std::vector<int>(l2 + 1, 0));
        dp[0][0] = true;
        for (int j = 0; j < l2; j++) {
            dp[0][j + 1] = s2[j] == s3[j] && dp[0][j];
        }
        for (int i = 0; i < l1; i++) {
            dp[i + 1][0] = s1[i] == s3[i] && dp[i][0];
            for (int j = 0; j < l2; j++) {
                dp[i + 1][j + 1] = (s1[i] == s3[i + j + 1] && dp[i][j + 1]) || (s2[j] == s3[i + j + 1] && dp[i + 1][j]);
            }
        }
        return dp[l1][l2];
    }
};