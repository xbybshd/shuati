class Solution {
public:
    string minWindow(string s, string t) {
        // less指的是s数组的窗口中，字母数量少于t的字母种类数
        int ans_left = -1, ans_right = s.size(), less, ans;
        int cnt[128] = { 0 };
        for (char& ti : t) {
            if (cnt[ti] == 0) {
                less++; // less窗口没包含的t的字母种类数，开始就是等于t的种类
            }
            cnt[ti]++;
        }
        int left = 0;
        for (int right = 0; right < s.length(); right++) {
            char c = s[right];
            cnt[c]--; // 窗口有字母了，cnt代表t比窗口多的，字母数量
            if (cnt[c] == 0) { // 说明对字母c来说，窗口已经包含了
                less--;
            }
            while (less == 0) { // 当已经满足一次包含条件的时候，开始进行移动left的判断
                if (right - left < ans_right - ans_left) {
                    ans = right - left;
                    ans_right = right;
                    ans_left = left;
                }
                char cl = s[left];
                if (cnt[cl] == 0) { // 说明left字母如果去除，那么窗口将不在完全包含cl
                    less++;
                }
                cnt[cl]++;
                left++;
            }
        }
        if (ans_left == -1)
            return "";
        else {
            return s.substr(ans_left, ans + 1);
        }
    }
};

class Solution {
public:
    string minWindow(string s, string t) {
        int l = 0, r = 0, al = -1, ar = s.size(), ans = 0, less = 0;
        int cnt[128] = { 0 };
        for (char& ti : t) {
            if (cnt[ti] == 0) {
                less++;
            }
            cnt[ti]++;
        }
        for (; r < s.length(); r++) {
            char c = s[r];
            cnt[c]--;
            if (cnt[c] == 0) {
                less--;
            }
            while (less == 0) {
                if (r - l < ar - al) {
                    ans = r - l;
                    ar = r;
                    al = l;
                }
                char cl = s[l];
                if (cnt[cl] == 0) {
                    less++;
                }
                cnt[cl]++;
                l++;
            }
        }
        if (al == -1) {
            return "";
        }
        else {
            return s.substr(al, ans + 1);
        }
    }
};