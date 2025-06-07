class Solution {
public:
    std::vector<int> v;
    std::vector<int> res;
    void dfs(std::vector<int>& nums, std::vector<std::vector<int>>& ans, int ni, int l) {
        v[ni] = 1;
        res.push_back(nums[ni]);
        if (l == nums.size() - 1) {
            ans.push_back(res);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            // 增加的条件是 i大于0的时候，如果后面与前面有重复，前面如果使用过了，可以继续，因为属于不同层
            // 如果前面没有使用过，就需要剪枝
            if (v[i] != 1 && !(i > 0 && nums[i] == nums[i - 1] && v[i - 1] == 0)) {
                dfs(nums, ans, i, l + 1);
                v[i] = 0;
                res.pop_back();
            }
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        v = std::vector<int>(nums.size(), 0);
        std::vector<std::vector<int>> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (i == 0 || (i > 0 && nums[i] != nums[i - 1])) {
                dfs(nums, ans, i, 0);
                v[i] = 0;
                res.pop_back();
            }
        }
        return ans;
    }
};

class Solution {
public:
    std::vector<int> v;
    std::vector<int> res;
    void dfs(std::vector<int>& nums, std::vector<std::vector<int>>& ans, int l) {
        if (l == nums.size()) {
            ans.push_back(res);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (v[i] == 1 || (i > 0 && nums[i] == nums[i - 1] && v[i - 1] == 0)) {
                continue;
            }
            v[i] = 1;
            res.push_back(nums[i]);
            dfs(nums, ans, l + 1);
            v[i] = 0;
            res.pop_back();
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        v = std::vector<int>(nums.size(), 0);
        std::vector<std::vector<int>> ans;
        dfs(nums, ans, 0);
        return ans;
    }
};
