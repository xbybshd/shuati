class Solution
{
public:
    int calculateMinimumHP(vector<vector<int>> &dungeon)
    {
        int n = dungeon.size();
        int m = dungeon[0].size();
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                int left = (j == m - 1) ? -10000 : dungeon[i][j + 1];
                int down = (i == n - 1) ? -10000 : dungeon[i + 1][j];
                if (i != n - 1 || j != m - 1)
                    dungeon[i][j] += max(left, down);                  //下一步方向只能是下或者右，那么反向时，取下或右的最大加上本格的数值
                dungeon[i][j] = dungeon[i][j] > 0 ? 0 : dungeon[i][j]; //如果最后数值大于0，就设为0，本格数值的意思是从本格开始走到最右下\
                需要的力气值，如果下一步就是补充的正的，就不需要额外加力气值了
            }
        }
        return dungeon[0][0] * -1 + 1;
    }
};