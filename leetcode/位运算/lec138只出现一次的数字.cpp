class Solution {
public:
    // 异或相当于自动取模的模2加法
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for (int x : nums) {
            ans ^= x;
        }
        return ans;
    }
};