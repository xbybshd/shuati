class Solution {
public:
    int maxSales(vector<int>& sales) {
        int ans = 0x80000000;
        std::vector<int> dp(sales.size() + 1, 0);
        for (int i = 1; i <= sales.size(); i++) {
            dp[i] = std::max(dp[i - 1] + sales[i - 1], sales[i - 1]);
            ans = std::max(dp[i], ans);
        }
        return ans;
    }
};
// 如果前面的加上现在的还小于现在的，那就抛弃前面的，直接从现在的开始