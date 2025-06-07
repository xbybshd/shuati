class Solution {
public:
    int lowerbound(std::vector<int>& nums, int target) {
        int l = 0, r = nums.size();
        while (l < r) {
            int mid = (l + r) >> 1;
            if (nums[mid] >= target) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return r;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.size() == 0) {
            return { -1, -1 };
        }
        int l = lowerbound(nums, target);
        if (l == nums.size() || nums[l] != target) {
            return { -1, -1 };
        }
        int r = lowerbound(nums, target + 1) - 1;
        return { l, r };
    }
};