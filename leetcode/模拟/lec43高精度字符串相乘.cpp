class Solution {
public:
    string multiply(string num1, string num2) {
        int n = num1.size(), m = num2.size();
        // nxm位数要么是n+m-1.要么是n+m,这种是最大值10的幂的情况
        if (num1[0] == '0' || num2[0] == '0') {
            return "0";
        }
        std::vector<int> ans(n + m, 0);
        // 先每位都相乘，结果存在i+j+1的位置，这些结果是对的，只是进制超过了10
        for (int i = n - 1; i >= 0; i--) {
            int ni = num1[i] - '0';
            for (int j = m - 1; j >= 0; j--) {
                int mi = num2[j] - '0';
                ans[i + j + 1] += ni * mi;
            }
        }
        // 下一步应该从后往前整理进制
        for (int i = ans.size() - 1; i > 0; i--) {
            if (ans[i] >= 10) {
                ans[i - 1] += ans[i] / 10;
                ans[i] = ans[i] % 10;
            }
        }
        std::string res;
        // 最后根据第0位是否被进位了，来确定字符串的起始添加位置
        int idx = ans[0] == 0 ? 1 : 0;
        for (; idx < ans.size(); idx++) {
            res.push_back(ans[idx] + '0');
        }
        return res;
    }
};