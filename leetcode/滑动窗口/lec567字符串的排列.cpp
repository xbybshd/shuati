class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.length(), m = s2.length();
        std::vector<int> cnt(26);
        for (char& c : s1) {
            cnt[c - 'a']++;
        }
        int left = 0;
        for (int i = 0; i < m; i++) {
            int c = s2[i] - 'a';
            cnt[c]--;
            while (cnt[c] < 0) {
                cnt[s2[left] - 'a']++;
                left++;
            }
            if (i - left + 1 == n) {
                return true;
            }
        }
        return false;
    }
};