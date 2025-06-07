class Solution {
public:
    // i从前往后，j从i开始往前试探单词集合的最大长度，i的状态由j+单词内的某一集合转变而来，要求j也是可以拆分的
    // 最开始的dp[0]是终点，开始默认可以拆分
    bool wordBreak(string s, vector<string>& wordDict) {
        int max_len = std::ranges::max(wordDict, {}, &std::string::length).length();
        unordered_set<std::string> words(wordDict.begin(), wordDict.end());
        int n = s.length();
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = i - 1; j >= std::max(i - max_len, 0); j--) {
                if (dp[j] && words.count(s.substr(j, i - j))) {
                    dp[i] = 1;
                    break;
                }
            }
        }
        return dp[n];
    }
};