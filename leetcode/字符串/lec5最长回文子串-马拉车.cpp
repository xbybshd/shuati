class Solution {
public:
    string longestPalindrome(string s) {
        std::string s1("$#");
        for (char& c : s) {
            s1 += c;
            s1 += "#";
        }
        int mid = 0, max_r = 0, ans_p = 0, ans_l = 1, len = s1.length();
        std::vector<int> p(2 * len + 3, 0);
        for (int i = 1; i < len; i++) {
            if (max_r >= i) {
                p[i] = std::min(p[(mid << 1) - i], max_r - i);
            }
            while (s1[i + p[i] + 1] == s1[i - p[i] - 1]) {
                p[i]++;
            }
            if (i + p[i] > max_r) {
                max_r = i + p[i];
                mid = i;
            }
            if (p[i] > ans_l) {
                ans_l = p[i];
                ans_p = (i - p[i]) >> 1; // 原始回文长度是偶数的时候，对称轴在#上，所以原始位置用i-p[i] >>1 计算
            }
        }
        std::string ans = s.substr(ans_p, ans_l);
        return ans;
    }
};