class Solution {
public:
    std::vector<int> res;
    int len = 0;
    int lengthOfLIS(vector<int>& nums) {
        res.reserve(2503);
        for (int i = 0; i < nums.size(); i++) {
            auto iter = std::lower_bound(res.begin(), res.end(), nums[i]);
            if (iter == res.end()) {
                res.push_back(nums[i]);
            }
            else {
                *iter = nums[i];
            }
        }
        int ans = res.size();
        return ans;
    }
};

// 维护一个数组，单调递增，遍历元素，每次遍历二分查找数组内第一个大于等于当前元素的位置，对其进行替换，到最后数组的最大长度就是最长上升子序列
// 可以成立的原因在与，