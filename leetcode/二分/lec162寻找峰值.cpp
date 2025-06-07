class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (nums[mid] > nums[mid + 1]) { //本质是寻找导数零点，从前往后，前大于后，导数小于零，那就缩短右边
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return l;
    }
};