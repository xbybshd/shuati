class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.length(), m = word2.length();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
        for (int i = 0; i <= n; i++) {
            dp[i][0] = i;
        }
        for (int i = 0; i <= m; i++) {
            dp[0][i] = i;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int left = dp[i][j - 1] + 1;
                int up = dp[i - 1][j] + 1;
                int left_up = dp[i - 1][j - 1] + 1;
                if (word1[i - 1] == word2[j - 1]) {
                    left_up--;
                }
                dp[i][j] = std::min(left_up, std::min(left, up));
            }
        }
        return dp[n][m];
    }
};

class Solution {
public:
#define MAX 999
    int dp[MAX][MAX]; // word1为i长度，word2为j长度，从word1转换为word2的编辑距离
    int minDistance(string word1, string word2) {
        int n1 = word1.length();
        int n2 = word2.length();

        for (int i = 0; i <= n1; i++) {
            dp[i][0] = i;
        }
        for (int i = 0; i <= n2; i++) {
            dp[0][i] = i;
        }
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                int left = dp[i][j - 1] + 1; // i,和j-1都算出来了，只要word2再加个j就行了
                int down = dp[i - 1][j] + 1; // i-1,和j都算出来了，只要word1再减个i就行了
                int left_down = dp[i - 1][j - 1] + 1; // i-1和j-1都算出来了，如果i，j不同，也要加1，代表我们知道i-1转移到j-1的步骤数，最后一个字母换一下即可
                if (word1[i - 1] == word2[j - 1])
                    left_down--; // 相同就减1
                dp[i][j] = min(left, min(down, left_down));
            }
        }
        return dp[n1][n2];
    }
};