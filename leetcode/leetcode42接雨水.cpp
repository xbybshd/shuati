class Solution
{
public:
    vector<int> lscan;
    int trap(vector<int> &height)
    {
        if (height.empty() || height.size() == 1)
            return 0;
        int lm = height[0];
        lscan.push_back(height[0]); //左向扫描，初始化第一个
        int len = height.size();
        int sum1 = height[0];
        for (int i = 1; i < len; i++)
        {
            sum1 += height[i];
            if (height[i] > lm)
            {
                lm = height[i]; //只加入最大的
                lscan.push_back(height[i]);
            }
            else
            {
                lscan.push_back(lm);
            }
        }
        int rm = height[len - 1];
        int all = 0;
        for (int i = len - 1; i >= 0; i--)
        {
            int nowr;
            if (height[i] > rm)
            {
                rm = height[i];
            }
            all += min(rm, lscan[i]);
        }
        int v = all - sum1;
        return v;
    }
};