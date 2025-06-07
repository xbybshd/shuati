class Solution {
public:
    std::vector<int> nums;
    std::vector<int> origin;
    Solution(vector<int>& nums) {
        this->nums = nums;
        origin = nums;
    }

    vector<int> reset() {
        nums = origin;
        return nums;
    }

    vector<int> shuffle() {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int k = i + rand() % (n - i);
            swap(nums[i], nums[k]);
        }
        return nums;
    }
};