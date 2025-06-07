class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        std::unordered_map<int, int> cnt { { 0, 1 } }; // 当前缀和刚好等于全序列的时候，作为提取标记
        int sum = 0;
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (cnt.contains(sum - k)) {
                ans += cnt[sum - k];
            }
            cnt[sum]++; // 要后插入
        }
        return ans;
    }
};