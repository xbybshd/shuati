class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int len = height.size();
        int maxv = 0;
        int i = 0;
        int j = len - 1;
        while (i < j)
        {
            int evl = (j - i) * min(height[i], height[j]);
            maxv = max(evl, maxv);
            if (height[i] < height[j]) //两边谁小移动谁
            {
                i++;
            }
            else
            {
                j--;
            }
        }
        return maxv;
    }
};