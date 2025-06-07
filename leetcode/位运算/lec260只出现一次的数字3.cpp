class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unsigned int xor_all = 0;
        for (int x : nums) {
            xor_all ^= x;
        }
        int lowbit = xor_all & -xor_all;
        std::vector<int> ans(2);
        for (int x : nums) {
            ans[(x & lowbit) != 0] ^= x;
        }
        return ans;
    }
};