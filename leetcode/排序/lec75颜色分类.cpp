class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1;
        for (int i = 0; i < n; i++) {
            // r是要单独动的，因为i和l是随i动，r是逆向，所以要单独
            while (i < r && nums[i] == 2) { // 将2换到后面，如果换回来的还是2，那就r--继续换
                swap(nums[i], nums[r]);
                r--;
            }
            if (nums[i] == 0) {
                swap(nums[l], nums[i]);
                l++;
            }
        }
    }
};