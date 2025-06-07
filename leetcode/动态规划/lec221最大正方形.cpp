class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int max_ans = 0;
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == '1') { // 只讨论矩阵值为1的情况
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    }
                    else { //取左上，上，左，最小值加1
                        dp[i][j] = std::min(dp[i - 1][j - 1], std::min(dp[i - 1][j], dp[i][j - 1])) + 1;
                    }
                    max_ans = std::max(max_ans, dp[i][j]);
                }
            }
        }
        return max_ans * max_ans;
    }
};