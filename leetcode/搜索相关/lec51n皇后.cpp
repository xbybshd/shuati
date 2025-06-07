class Solution {
public:
    int rows[10] = { 0 };
    int left[18] = { 0 };
    int right[19] = { 0 };
    std::vector<int> v;
    std::vector<std::vector<int>> ans;
    void dfs(int ni, int n) {
        if (ni == n) {
            ans.emplace_back(v);
            return;
        }
        for (int i = 0; i < n; i++) {
            if (rows[i] == 0 && left[i + ni] == 0 && right[n - 1 - (ni - i)] == 0) {
                v[ni] = i;
                rows[i] = 1;
                left[i + ni] = 1;
                right[n - 1 - ni + i] = 1;
                dfs(ni + 1, n);
                v[ni] = 0;
                rows[i] = 0;
                left[i + ni] = 0;
                right[n - 1 - ni + i] = 0;
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        v = std::vector<int>(n, 0);
        std::vector<std::string> ans_elem(n, std::string(n, '.'));
        std::vector<std::vector<std::string>> res;
        dfs(0, n);
        for (auto& vec : ans) {
            res.emplace_back(ans_elem);
            auto& back = res.back();
            for (int i = 0; i < back.size(); i++) {
                back[i][vec[i]] = 'Q';
            }
        }
        return res;
    }
};