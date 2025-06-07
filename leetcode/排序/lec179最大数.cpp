class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> str;
        for (auto i : nums) {
            str.push_back(to_string(i));
        }
        // 使用 lambda 比较 elements.
        auto cmp = [](string left, string right) {
            return left + right > right + left;
        };
        sort(str.begin(), str.end(), cmp);
        stringstream ss;
        for (auto c : str) {
            ss << c;
        }
        string ans = ss.str();
        if (ans[0] == '0') {
            return "0";
        }
        return ans;
    }
};