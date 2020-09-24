class Solution
{
public:
#define MAX 103
    int dp[MAX][MAX] = {0};
    int minCost(int n, vector<int> &cuts)
    {
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        int num = cuts.size() - 1;
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 0; i <= num; i++) //初始化，闭区间，绳子重合区间和大小为1的区间代价为0；
        {
            dp[i][i] = 0;
            if (i < num)
                dp[i][i + 1] = 0;
        }
        for (int len = 1; len <= num; len++) //区间dp模板，三轮循环
        {
            for (int i = 0; i <= num - len; i++)
            {
                int j = i + len;
                for (int k = i; k <= j; k++)
                {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]); //区间dp内部遍历，可以去首尾点
                }
                if (j - i > 1) //关键，只有不相邻两点，才看做切绳子，才有代价，而且每合并一个区间都要加上代价，其最小化在上一步完成
                    dp[i][j] += (cuts[j] - cuts[i]);
            }
        }
        return dp[0][num];
    }
};