class Solution
{
    typedef long long ll;

public:
    int c[10000] = {0};
    int numTrees(int n)
    {
        c[0] = c[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                c[i] += (c[j - 1] * c[i - j]);
            }
        }
        return c[n];
    }
};