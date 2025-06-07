class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        int ans = n == 1 ? triangle[0][0] : 0x3f3f3f3f;
        for (int i = 1; i < n; i++) {
            int m = triangle[i].size();
            for (int j = 0; j < m; j++) {
                if (j == 0) {
                    triangle[i][j] += triangle[i - 1][j];
                }
                else if (j == m - 1) {
                    triangle[i][j] += triangle[i - 1][j - 1];
                }
                else {
                    triangle[i][j] += std::min(triangle[i - 1][j - 1], triangle[i - 1][j]);
                }
                if (i == n - 1) {
                    ans = std::min(ans, triangle[i][j]);
                }
            }
        }
        return ans;
    }
};