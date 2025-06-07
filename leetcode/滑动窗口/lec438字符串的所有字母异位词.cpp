class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        std::vector<int> cnt(26);
        for (char& c : p) {
            cnt[c - 'a']++;
        }
        std::vector<int> ans;
        int n = s.length(), m = p.length(), left = 0;
        // 如果右端某字母进入之后，数量大于p那就让左端前进所见，保证每一个字符数量都小于等于p，如果左右之差是p的长度，那就说明找到了
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            cnt[c]--;
            while (cnt[c] < 0) {
                cnt[s[left] - 'a']++;
                left++;
            }
            if (i - left + 1 == m) {
                ans.push_back(left);
            }
        }
        return ans;
    }
};