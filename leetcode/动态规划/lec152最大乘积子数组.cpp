int maxProduct(vector<int>& nums) {
    long maxf, minf, ans;
    maxf = minf = ans = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        long mx = maxf, mn = minf;
        maxf = std::max(mx * nums[i], std::max((long)nums[i], mn * nums[i]));
        minf = std::min(mn * nums[i], std::min((long)nums[i], mx * nums[i]));
        ans = std::max(ans, maxf);
    }
    return ans;
}