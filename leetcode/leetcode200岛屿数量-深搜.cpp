class Solution
{
public:
    int w[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int lenc, lenr;

    void dfs(int ni, int nj, vector<vector<char>> &grid)
    {
        if (grid[ni][nj] == '2' || grid[ni][nj] == '0')
            return;
        grid[ni][nj] = '2';
        for (int i = 0; i < 4; i++)
        {
            int u = ni + w[i][0];
            int v = nj + w[i][1];
            if (u >= 0 && u < lenr && v >= 0 && v < lenc)
                dfs(u, v, grid);
        }
    }
    int numIslands(vector<vector<char>> &grid)
    {
        lenr = grid.size();
        if (!lenr)
            return 0;
        lenc = grid[0].size();

        int ans = 0;
        for (int i = 0; i < lenr; i++)
        {
            for (int j = 0; j < lenc; j++)
            {
                if (grid[i][j] == '1')
                {
                    dfs(i, j, grid);
                    ans++;
                }
            }
        }
        return ans;
    }
};