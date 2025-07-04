class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (nums[mid] == nums[r]) { // 如果mid和r一样，r--，因为是一样跳过最右边，不会遗漏最小值
                r--;
            }
            else if (nums[mid] >= nums[r]) {
                l = mid + 1;
            }
            else {
                r = mid;
            }
        }
        return nums[r];
    }
};