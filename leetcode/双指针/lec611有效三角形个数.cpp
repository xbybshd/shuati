class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n - 2; i++) {
            int ui = nums[i];
            if (ui == 0) {
                continue;
            }
            int j = i + 1;
            for (int k = i + 2; k < n; k++) {
                while (ui + nums[j] <= nums[k]) {
                    j++;
                }
                ans += k - j;
            }
        }
        return ans;
    }
};

// i _ _ _ _ _ _
// _ _ _ _ k _ _
// _ _ j _ _ _ _
// i外层固定，k从小到大，j从小到大，关键在于，i+j>k的时候，如果k继续第二轮增加，j只有一个方向可以移动。双指针要使内部循环两个指针都只能朝一个方向

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        ranges::sort(nums);
        int ans = 0;
        for (int k = nums.size() - 1; k > 1; k--) {
            int c = nums[k];
            if (nums[0] + nums[1] > c) { // 优化一
                ans += (k + 1) * k * (k - 1) / 6;
                break;
            }
            if (nums[k - 2] + nums[k - 1] <= c) { // 优化二
                continue;
            }
            int i = 0; // a=nums[i]
            int j = k - 1; // b=nums[j]
            while (i < j) {
                if (nums[i] + nums[j] > c) {
                    ans += j - i;
                    j--;
                }
                else {
                    i++;
                }
            }
        }
        return ans;
    }
};
// i _ _ _ _ _ _
// _ _ _ _ _ k _
// _ _ _ _ j _ _
// k 从大到小，i j在两边，i+j>k的时候此时i++依然会大于，所以只能j减小，否则i只能增加