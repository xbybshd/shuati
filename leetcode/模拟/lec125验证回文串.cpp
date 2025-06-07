class Solution {
public:
    bool isPalindrome(string s) {
        std::string sa;
        for (char ch : s) {
            if (isalnum(ch)) {
                sa += tolower(ch);
            }
        }
        int n = sa.size();
        int l = 0, r = n - 1;
        while (l < r) {
            if (sa[l] != sa[r]) {
                return false;
            }
            l++;
            r--;
        }
        return true;
    }
};