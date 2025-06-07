class Solution {
public:
    string addStrings(string num1, string num2) {
        int n1 = num1.size() - 1;
        int n2 = num2.size() - 1;
        int proceed = 0;
        int elm1, elm2, res;
        std::string ans;
        while (n1 >= 0 || n2 >= 0 || proceed) {
            elm1 = n1 >= 0 ? num1[n1--] - '0' : 0;
            elm2 = n2 >= 0 ? num2[n2--] - '0' : 0;
            res = elm1 + elm2 + proceed;
            ans.push_back(res % 10 + '0');
            proceed = res / 10;
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};