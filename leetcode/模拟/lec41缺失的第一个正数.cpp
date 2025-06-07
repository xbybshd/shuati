class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int& ni : nums) { // 先把所有的负数变成n+1，因为只需要正整数
            if (ni <= 0) {
                ni = n + 1;
            }
        }
        for (int i = 0; i < n; i++) { // 此时已经不存在开始的负数，开始遍历，把小于等于n的数跳出来，把这些数减一的位置的数，设为负值
            // 注意此时已经出现负数了，所以如果被设为负数的数，也要进行操作，就需要用他们的绝对值
            // 会存在重复数的情况，这样会两次修改同一个位置第一次为负数，第二次如果不用abs就又返回正数了，所以也要用绝对值
            int real_n = abs(nums[i]);
            if (real_n <= n) {
                nums[real_n - 1] = -abs(nums[real_n - 1]);
            }
        }
        for (int i = 0; i < n; i++) {
            //从左往右，遍历到的第一个没有被设为负数的索引，就是最小未被包含的正数
            if (nums[i] > 0) {
                return i + 1;
            }
        }
        return n + 1;
    }
};