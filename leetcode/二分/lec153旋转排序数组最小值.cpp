class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (nums[mid] >= nums[r]) { //这里求最小值，mid大于等于r必然不是可行解，所以用它更新l
                l = mid + 1;
            }
            else {
                r = mid;
            }
        }
        return nums[r];
    }
};