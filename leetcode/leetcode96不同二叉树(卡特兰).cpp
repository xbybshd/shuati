class Solution
{ //实质是求卡特兰
    typedef long long ll;

public:
    ll c[100] = {0};
    int numTrees(int n)
    {
        c[0] = 1;
        int n2 = n << 1;
        for (int i = 1; i <= n2; i++)
        {
            for (int j = i; j >= 1; j--)
            {
                c[j] = c[j - 1] + c[j]; //组合数不带取余标准滚动数组做法
            }
        }
        int ans = c[n] / (n + 1);
        return ans;
    }
};