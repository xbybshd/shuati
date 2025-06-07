class Solution {
public:
    int w[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
    std::vector<std::vector<int>> visit;
    int n, m, ans;
    int dfs(int x, int y, vector<vector<int>>& matrix) {
        if (visit[x][y] != 0) {
            return visit[x][y];
        }
        visit[x][y] = -1;
        int max_len = 0;
        for (auto& [dx, dy] : w) {
            int xi = x + dx, yi = y + dy;
            if (xi >= 0 && xi < n && yi >= 0 && yi < m && visit[xi][yi] != -1 && matrix[xi][yi] > matrix[x][y]) {
                max_len = std::max(max_len, dfs(xi, yi, matrix));
            }
        }
        visit[x][y] = max_len + 1;
        return visit[x][y];
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        n = matrix.size();
        m = matrix[0].size();
        visit = std::move(std::vector<std::vector<int>>(n, std::vector<int>(m, 0)));
        int max_ans = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                max_ans = std::max(dfs(i, j, matrix), max_ans);
            }
        }
        return max_ans;
    }
};