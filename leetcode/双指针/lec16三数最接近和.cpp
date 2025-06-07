class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int ans = 30000;
        int res = 0;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            int left = target - nums[i];
            int j = i + 1, k = nums.size() - 1;
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    j++;
                }
                else if (k < nums.size() - 1 && nums[k] == nums[k + 1]) {
                    k--;
                }
                else if (sum > target) {
                    if (abs(target - sum) < ans) {
                        ans = abs(target - sum);
                        res = sum;
                    }
                    k--;
                }
                else if (sum < target) {
                    if (abs(target - sum) < ans) {
                        ans = abs(target - sum);
                        res = sum;
                    }
                    j++;
                }
                else {
                    return target;
                }
            }
        }
        return res;
    }
};