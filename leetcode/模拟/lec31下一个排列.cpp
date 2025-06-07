class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i = n - 2; // 从右边第二个开始，从右向左，找此数右边大于此数的数，用while包含条件
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }
        // 没找到，i为-1，直接进入最后，说明整个排列是单调递减的已经是最大了，下一个是最小的第一个排列，直接全部反转就行
        if (i >= 0) {
            // 从最后一个开始，找最小的大于i的数，因为i的寻找过程中，i到i右边第一个是递增，之后全是递减，所以只要从后往前遍历
            int j = n - 1;
            while (nums[i] >= nums[j]) {
                j--;
            }
            // 这里都不能是等于，等于是被排出的
            std::swap(nums[i], nums[j]);
        }
        std::reverse(nums.begin() + i + 1, nums.end());
    }
};