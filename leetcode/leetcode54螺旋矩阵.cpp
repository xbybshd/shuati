class Solution
{
public:
    int w[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
#define MAX 0x3f3f3f3f
    int row, cow;
    bool cursh(int i, int j, vector<vector<int>> &matrix, int forward)
    {
        int ui = i + w[forward][0];
        int uj = j + w[forward][1];
        if (ui < row && ui >= 0 && uj < cow && uj >= 0 && matrix[ui][uj] != MAX)
        {
            return true;
        }
        return false;
    }
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        vector<int> va;
        if (matrix.size() == 0)
            return va;
        int i = 0;
        int j = 0;
        int forward = 0; //当前方向数组索引
        row = matrix.size();
        cow = matrix[0].size();
        int cur = 0; //当前节点转换方向次数
        while (cur != 4)
        { //换了4次方向说明结束
            if (cur == 0)
            { //转换次数为0，说明到了新节点
                va.push_back(matrix[i][j]);
                matrix[i][j] = MAX;
                //printf("%d %d %d\n",matrix[i][j],i,j);
            }
            if (cursh(i, j, matrix, forward))
            {                       //判断当前方向往前走一格是否可以
                i += w[forward][0]; //可以就继续走，方向次数置为0
                j += w[forward][1];
                cur = 0;
            }
            else
            {
                cur++; //不可以就加1，换方向
                forward++;
                forward %= 4;
            }
        }
        return va;
    }
};