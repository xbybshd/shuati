class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();
        int i = 0, j = m - 1;
        while (i < n && j >= 0) {
            if (matrix[i][j] == target) {
                return true;
            }
            if (matrix[i][j] > target) { // 当前数大于target，说明当前列往下都是大于的，所以当前列不能往下，要么往上，要么往左，
                // 从右上角开始限制了往上，所以是往左
                j--;
            }
            else {
                i++; // 一次类推，右上到左下 target小于当前往下走
            }
        }
        return false;
    }
};