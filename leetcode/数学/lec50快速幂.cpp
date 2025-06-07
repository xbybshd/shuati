class Solution {
public:
    double myPow(double x, int n) {
        double ans = 1;
        long long ni = n; // 防止负数变正溢出
        if (ni < 0) {
            ni = -ni;
            x = 1 / x;
        }
        while (ni) {
            if (ni & 1) {
                ans *= x;
            }
            x *= x;
            ni >>= 1;
        }
        return ans;
    }
};