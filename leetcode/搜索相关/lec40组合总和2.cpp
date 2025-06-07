class Solution {
public:
    std::vector<int> res;
    void dfs(vector<vector<int>>& ans, vector<int>& candidates, int idx, int left) {
        if (left == 0) {
            ans.emplace_back(res);
            return;
        }
        // 组合是需要从前往后搜索，单个位置不能进入第二次，后面不进入前面的
        // 但是组合有重复元素，要求深搜路径上的，就是当前1，进入下一层是另一个1，这样可以接受
        // 当前层的循环上，同一层1和1不能选
        // 如果有1，1，1三个，01，02是可以接受，但是01，03相当于03跟02并列了，不能接受
        // 循环终止条件有个剪枝，因为是排序过的，如果当前i超过了left，那后面也肯定超过
        for (int i = idx + 1; i < candidates.size() && candidates[i] <= left; i++) {
            if (i != idx + 1 && candidates[i] == candidates[i - 1]) {
                continue;
            }
            res.push_back(candidates[i]);
            dfs(ans, candidates, i, left - candidates[i]);
            res.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans;
        dfs(ans, candidates, -1, target);
        return ans;
    }
};

class Solution {
public:
    std::vector<int> res;
    void dfs(vector<vector<int>>& ans, vector<int>& candidates, int idx, int left) {
        if (left == 0) {
            ans.emplace_back(res);
            return;
        }
        // 循环可以是当前i，但是下面dfs可以是+1，这样最外层可以从0开始
        for (int i = idx; i < candidates.size() && candidates[i] <= left; i++) {
            if (i != idx && candidates[i] == candidates[i - 1]) {
                continue;
            }
            res.push_back(candidates[i]);
            dfs(ans, candidates, i + 1, left - candidates[i]);
            res.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans;
        dfs(ans, candidates, 0, target);
        return ans;
    }
};