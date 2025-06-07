class Solution {
public:
    int w[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
    int n, m, len;
    bool dfs(int ni, int mi, int k, vector<vector<char>>& board, string& word) {
        if (board[ni][mi] != word[k]) {
            return false;
        }
        if (k + 1 == len) {
            return true;
        }
        board[ni][mi] = 0;
        for (auto& [dx, dy] : w) {
            int x = ni + dx, y = mi + dy;
            if (0 <= x && x < n && 0 <= y && y < m && board[x][y] != 0 && dfs(x, y, k + 1, board, word)) {
                return true;
            }
        }
        board[ni][mi] = word[k];
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        n = board.size();
        m = board[0].size();
        len = word.length();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (dfs(i, j, 0, board, word)) {
                    return true;
                }
            }
        }
        return false;
    }
};