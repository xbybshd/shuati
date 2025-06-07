class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int sum = 0, n = nums.size();
        int ans = n + 1;
        int i = 0;
        for (int j = 0; j < n; j++) {
            sum += nums[j];
            while (sum - nums[i] >= target) { // 为什么要减去nums[i]，因为是希望刚好卡在刚刚大于sum的第一个数上，所以要有这一步
                sum -= nums[i];
                i++;
            }
            if (sum >= target) {
                ans = std::min(ans, j - i + 1);
            }
        }
        return ans <= n ? ans : 0;
    }
};