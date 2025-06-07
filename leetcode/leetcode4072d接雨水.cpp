class Solution {
public:
    int w[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
    int trapRainWater(vector<vector<int>>& heightMap) {
        std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<>> que;
        int ans = 0, gloal_minh = 0;
        int row = heightMap.size(), cow = heightMap[0].size();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < cow; j++) {
                if (i == 0 || j == 0 || i == row - 1 || j == cow - 1) {
                    que.emplace(heightMap[i][j], i, j);
                    heightMap[i][j] = -1;
                }
            }
        }
        while (!que.empty()) {
            auto [minh, x, y] = que.top();
            que.pop();
            for (auto& [ni, nj] : w) {
                int nx = x + ni;
                int ny = y + nj;
                if (nx >= 0 && ny >= 0 && nx < row && ny < cow && heightMap[nx][ny] >= 0) {
                    ans += std::max(minh - heightMap[nx][ny], 0);
                    que.emplace(std::max(minh, heightMap[nx][ny]), nx, ny);
                    heightMap[nx][ny] = -1;
                }
            }
        }
        return ans;
    }
};