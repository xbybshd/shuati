class Solution {
public:
    std::string str[10] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
    std::string res;
    int n;
    void dfs(int ni, std::string& digits, std::vector<std::string>& ans) {
        if (ni == n) {
            ans.push_back(res);
            return;
        }
        for (char& c : str[digits[ni] - '0']) {
            res[ni] = c;
            dfs(ni + 1, digits, ans);
        }
    }
    vector<string> letterCombinations(string digits) {
        std::vector<std::string> ans;
        n = digits.length();
        if (!n) {
            return ans;
        }
        res = std::string(n, '0');
        dfs(0, digits, ans);
        return ans;
    }
};