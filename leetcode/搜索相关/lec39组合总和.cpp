class Solution {
public: // 枚举选哪个的做法，
    std::vector<int> res;
    std::vector<std::vector<int>> ans;
    void dfs(std::vector<int>& candidates, int idx, int left) {
        if (left == 0) {
            ans.emplace_back(res);
            return;
        }
        if (left < candidates[idx]) {
            return;
        }
        for (int i = idx; i < candidates.size(); i++) {
            res.push_back(candidates[i]);
            dfs(candidates, i, left - candidates[i]);
            res.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        dfs(candidates, 0, target);
        return ans;
    }
};