class Solution {
public:
    int numSquares(int n) {
        std::vector<int> sq(102, 0);
        for (int i = 1; i <= 100; i++) {
            sq[i] = i * i;
        }
        std::vector<int> dp(n + 1, 0x3f3f3f3f);
        int st = sqrt(n);
        dp[0] = 0;
        for (int i = 1; i <= st; i++) {
            int cost = sq[i];
            for (int j = cost; j <= n; j++) {
                dp[j] = std::min(dp[j], dp[j - cost] + 1);
            }
        }
        return dp[n];
    }
};