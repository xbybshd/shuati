class Solution {
public:
    int num, left_num, right_num, total;
    std::string res;
    char w[2] = { '(', ')' };
    void dfs(int pos, std::vector<std::string>& ans, int ni) {
        res.push_back(w[ni]);
        if (ni == 0) {
            left_num--;
            total++;
        }
        else {
            right_num--;
            total--;
        }
        if (pos == num - 1) {
            ans.emplace_back(res);
            return;
        }
        if (total + 1 >= 0 && left_num - 1 >= 0) {
            dfs(pos + 1, ans, 0);
            total--;
            left_num++;
            res.pop_back();
        }
        if (total - 1 >= 0 && right_num - 1 >= 0) {
            dfs(pos + 1, ans, 1);
            res.pop_back();
            right_num++;
            total++;
        }
    }

    vector<string> generateParenthesis(int n) {
        std::vector<std::string> ans_vec;
        num = 2 * n;
        left_num = n;
        right_num = n;
        total = 0;
        dfs(0, ans_vec, 0);
        return ans_vec;
    }
};

class Solution {
public:
    int num, left_total;
    std::string res;
    void dfs(int left_num, int pos, std::vector<std::string>& ans) {
        if (pos == num) {
            ans.emplace_back(res);
            return;
        }
        if (left_num < left_total) {
            res.push_back('(');
            dfs(left_num + 1, pos + 1, ans);
            res.pop_back();
        }
        if (pos - left_num < left_num) {
            res.push_back(')');
            dfs(left_num, pos + 1, ans);
            res.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        std::vector<std::string> ans_vec;
        left_total = n;
        num = 2 * n;
        dfs(0, 0, ans_vec);
        return ans_vec;
    }
};