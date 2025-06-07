class Solution {
public:
    std::vector<int> res;
    int n;
    void dfs(int i, std::vector<int>& nums, std::vector<std::vector<int>>& ans) {
        ans.push_back(res); // 每次进入都加一次结果
        for (int j = i; j < n; j++) { // 循环从当前索引开始，之前就不要了
            res.push_back(nums[j]);
            dfs(j + 1, nums, ans); // 下一个位置的结果从当前循环j的位置开始，模拟[i,i+x]这种跳过当前循环j的行为；
            res.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        n = nums.size();
        std::vector<std::vector<int>> ans;
        dfs(0, nums, ans);
        return ans;
    }
};