class Solution {
public:
    int max_ans = 0;
    int w[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
    int n, m;
    void dfs(vector<vector<int>>& grid, int ni, int mi, int& area) {
        int val = grid[ni][mi];
        if (val == 0 || val == -1) {
            return;
        }
        area++;
        grid[ni][mi] = -1;
        for (int i = 0; i < 4; i++) {
            int nj = ni + w[i][0];
            int mj = mi + w[i][1];
            if (nj >= 0 && nj < n && mj >= 0 && mj < m) {
                dfs(grid, nj, mj, area);
            }
        }
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int ans = 0;
                dfs(grid, i, j, ans);
                max_ans = std::max(max_ans, ans);
            }
        }
        return max_ans;
    }
};