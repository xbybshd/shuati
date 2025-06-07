class Solution {
public:
    std::unordered_map<int, int> v;
    int res[6] = { 0 };
    void dfs(vector<int>& nums, vector<vector<int>>& ans, int l, int ni) {
        v[ni] = 1;
        res[l] = ni;
        if (l == nums.size() - 1) {
            ans.emplace_back(res, res + l + 1);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (v[nums[i]] == 0) {
                dfs(nums, ans, l + 1, nums[i]);
                v[nums[i]] = 0;
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            v[nums[i]] = 0;
        }
        vector<vector<int>> ans;
        for (int i = 0; i < nums.size(); i++) {
            dfs(nums, ans, 0, nums[i]);
            v[nums[i]] = 0;
        }
        return ans;
    }
};

class Solution {
public:
    std::unordered_map<int, int> v;
    int res[6] = { 0 };
    void dfs(vector<int>& nums, vector<vector<int>>& ans, std::vector<int>& v, int l) {
        if (l == nums.size()) {
            ans.emplace_back(res, res + l);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (v[i] == 0) {
                v[i] = 1;
                res[l] = nums[i];
                dfs(nums, ans, v, l + 1);
                v[i] = 0;
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        std::vector<int> v(nums.size(), 0);
        vector<vector<int>> ans;
        dfs(nums, ans, v, 0);
        return ans;
    }
};