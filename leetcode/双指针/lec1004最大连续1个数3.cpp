class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size(), left = 0, right = 0, cnt = 0, ans = 0;
        for (; right < n; right++) {
            if (nums[right] == 0) {
                cnt++;
            }
            while (cnt > k && left <= right) {
                if (nums[left] == 0) { // 应该先减去当前left的0，再移动left
                    cnt--;
                }
                left++;
            }
            ans = std::max(ans, right - left + 1);
        }
        return ans;
    }
};