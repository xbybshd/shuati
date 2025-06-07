class Solution {
public:
    string removeKdigits(string num, int k) {
        std::vector<char> sp;
        int n = num.length();
        if (n <= k)
            return "0";
        for (int i = 0; i < n; i++) {
            while (!sp.empty() && num[i] < sp.back() && k > 0) {
                sp.pop_back();
                k--;
            }
            sp.push_back(num[i]);
        }
        for (; k > 0; k--) {
            sp.pop_back();
        }
        int i = 0;
        std::string ans;
        while (i < sp.size() && sp[i] == '0') {
            i++;
        }
        for (; i < sp.size(); i++) {
            ans += sp[i];
        }
        return ans.length() == 0 ? "0" : ans;
    }
};