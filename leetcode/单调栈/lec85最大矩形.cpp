class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        std::vector<int> height(m + 2, 0); // 这里需要前面后面都要加上0
        std::stack<int> sp;
        int max_ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == '1') {
                    height[j + 1]++;
                }
                else {
                    height[j + 1] = 0;
                }
            }
            for (int j = 0; j < m + 2; j++) {
                while (!sp.empty() && height[sp.top()] > height[j]) {
                    int h = height[sp.top()];
                    sp.pop();
                    int left = sp.top() + 1;
                    int right = j - 1;
                    max_ans = std::max(h * (right - left + 1), max_ans);
                }
                sp.push(j);
            }
        }
        return max_ans;
    }
};