class Solution {
public:
    // 从开始来看，i i0首先遇到非0，那就一起移动，自交换，然后遇到0，i继续移动，
    // 如果开始是0，i继续移动，i0因为没有进入if，所以不动，等i进入非0，进入if，开始交换，i0++，此时i0与0会绑定
    // 如果有多个0，那i0始终与最前面0在一起
    void moveZeroes(vector<int>& nums) {
        int i0 = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                swap(nums[i], nums[i0]);
                i0++;
            }
        }
    }
};