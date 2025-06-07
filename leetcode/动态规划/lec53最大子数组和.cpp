int maxSubArray(vector<int>& nums) {
    int max_ans = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        nums[i] = std::max(nums[i], nums[i] + nums[i - 1]);
        max_ans = std::max(max_ans, nums[i]);
    }
    return max_ans;
}

// 类似 max[i] = max(num[i],max[i-1]*num[i])  如果之前的最大值加上当前都比不过当前，就没必要记录了