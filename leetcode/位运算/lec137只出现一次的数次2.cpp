class Solution {
public:
    // 其他都出现三次，只有一个有一次，就是对所有的位数的1做模3加法，最后余数就是这个数对应的位数
    int singleNumber(vector<int>& nums) {
        int a = 0, b = 0;
        for (int x : nums) {
            b = (x ^ b) & ~a;
            a = (x ^ a) & ~b;
        }
        return b;
    }
};