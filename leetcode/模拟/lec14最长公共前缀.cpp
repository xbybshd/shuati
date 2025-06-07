class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string& s0 = strs[0];
        for (int i = 0; i < s0.size(); i++) { // 取一个扫描
            for (string& s : strs) {
                if (i == s0.size() || s0[i] != s[i]) { // 中间中断到目前为止
                    return s0.substr(0, i);
                }
            }
        }
        return s0;
    }
};