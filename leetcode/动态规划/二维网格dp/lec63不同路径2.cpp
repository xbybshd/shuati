class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
        dp[0][1] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i + 1][j + 1] = 0;
                    continue;
                }
                else {
                    dp[i + 1][j + 1] = dp[i][j + 1] + dp[i + 1][j];
                }
            }
        }
        return dp[n][m];
    }
};