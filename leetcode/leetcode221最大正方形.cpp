class Solution
{

public:
    int m[300][300] = {0};
    int maximalSquare(vector<vector<char>> &matrix)
    {

        int row = matrix.size();
        if (!row)
            return 0;
        int cow = matrix[0].size();
        int max_ans = 0;
        for (int i = 1; i <= row; i++)
        {
            for (int j = 1; j <= cow; j++)
            {
                int left_up;
                int up;
                int left;
                up = m[i - 1][j];
                left = m[i][j - 1];
                left_up = m[i - 1][j - 1];
                m[i][j] = (matrix[i - 1][j - 1] == '0') ? 0 : (min(min(up, left), left_up) + 1); //当前点为0，就是0，否则是左上，上，左，三个最小值加1
                max_ans = max(max_ans, m[i][j]);
            }
        }
        return max_ans * max_ans;
    }
};