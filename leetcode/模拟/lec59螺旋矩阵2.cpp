class Solution {
public:
    int w[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
    vector<vector<int>> generateMatrix(int n) {
        std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));
        int idx = 1, len = n * n, direct = 0, x = 0, y = 0;
        while (idx <= len) {
            mat[x][y] = idx;
            idx++;
            int xi = x + w[direct][0], yi = y + w[direct][1];
            if (xi == n || yi == n || xi == -1 || yi == -1 || mat[xi][yi] != 0) {
                direct = (direct + 1) % 4;
            }
            x += w[direct][0];
            y += w[direct][1];
        }
        return mat;
    }
};