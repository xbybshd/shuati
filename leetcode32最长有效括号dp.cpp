class Solution
{
public:
#define MAX 100000
    int dp[MAX];
    int longestValidParentheses(string s)
    {
        int len = s.length();
        int maxn = 0;
        for (int i = 1; i < len; i++)
        {
            if (s[i] == ')')
            {
                if (s[i - 1] == '(')
                {
                    dp[i] = 2;
                    if (i - 1 > 0)
                    {
                        dp[i] += dp[i - 2];
                    }
                }
                else if (dp[i - 1] > 0)
                {
                    if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(')
                    {
                        dp[i] = dp[i - 1] + 2;
                        if (i - dp[i - 1] - 2 >= 0)
                        {
                            dp[i] += dp[i - dp[i - 1] - 2];
                        }
                    }
                }
            }
            maxn = max(maxn, dp[i]);
        }
        return maxn;
    }
};