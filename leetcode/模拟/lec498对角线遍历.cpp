class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        int p = n + m;
        std::vector<int> res;
        for (int i = 0; i < p - 1; i++) {
            if (i % 2 == 1) {
                int x = i < m ? 0 : i - m + 1;
                int y = i < m ? i : m - 1;
                while (x < n && y >= 0) {
                    res.emplace_back(mat[x][y]);
                    x++;
                    y--;
                }
            }
            else {
                int x = i < n ? i : n - 1;
                int y = i < n ? 0 : i - n + 1;
                while (x >= 0 && y < m) {
                    res.emplace_back(mat[x][y]);
                    x--;
                    y++;
                }
            }
        }
        return res;
    }
};