class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size(), m = matrix[0].size();
        int l = 0, r = m * n - 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int x = matrix[mid / m][mid % m];
            if (x == target) {
                return true;
            }
            else if (x < target) {
                l = mid + 1;
            }
            else if (x > target) {
                r = mid - 1;
            }
        }
        return false;
    }
};