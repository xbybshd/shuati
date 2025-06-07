class Solution {
public:
    bool checkValidString(string s) {
        int n = s.length();
        int min_ans = 0, max_ans = 0;
        for (int i = 0; i < n; i++) {
            char c = s[i];
            if (c == '(') {
                max_ans++;
                min_ans++;
            }
            else if (c == ')') {
                max_ans--;
                if (min_ans > 0)
                    min_ans--;
            }
            else {
                max_ans++;
                if (min_ans > 0)
                    min_ans--;
            }
            if (max_ans < 0) {
                return false;
            }
        }
        return min_ans == 0;
    }
};