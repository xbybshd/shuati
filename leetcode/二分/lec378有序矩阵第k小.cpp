class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size(), m = matrix[0].size();
        int l = matrix[0][0], r = matrix[n - 1][m - 1];
        while (l < r) {
            int mid = (l + r) >> 1;
            int count = 0;
            int j = n - 1;
            for (int i = 0; i < n; i++) {
                while (j >= 0 && matrix[i][j] > mid) { // 虽然l和r并没有代表具体的矩阵元素，但是求得的mid会被matrix[i][j]判断
                    // 会围绕k的具体矩阵元素数值，就count前后浮动，最后完全缩小范围
                    j--;
                }
                count += j + 1;
            }
            if (count < k) {
                l = mid + 1;
            }
            else {
                r = mid;
            }
        }
        return l;
    }
};