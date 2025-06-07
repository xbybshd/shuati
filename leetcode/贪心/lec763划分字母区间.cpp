class Solution {
public:
    vector<int> partitionLabels(string s) {
        int n = s.length();
        int cnt[26];
        for (int i = 0; i < n; i++) {
            cnt[s[i] - 'a'] = i;
        }
        std::vector<int> ans;
        int end = 0, start = 0;
        ;
        for (int i = 0; i < n; i++) {
            end = std::max(cnt[s[i] - 'a'], end);
            if (end == i) {
                ans.push_back(end - start + 1);
                start = end + 1;
            }
        }
        return ans;
    }
};