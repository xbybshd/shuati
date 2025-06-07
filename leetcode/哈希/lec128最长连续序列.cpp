class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int ans = 0;
        unordered_set<int> sp(nums.begin(), nums.end());
        for (int x : sp) {
            if (sp.contains(x - 1)) {
                continue;
            }
            int y = x + 1;
            while (sp.contains(y)) {
                y++;
            }
            ans = std::max(y - x, ans);
        }
        return ans;
    }
};