class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> ans(n, -1);
        std::stack<int, std::vector<int>> sp;
        for (int ni = 0; ni < 2 * n; ni++) {
            int i = ni % n;
            while (!sp.empty() && nums[i] > nums[sp.top()]) {
                ans[sp.top()] = nums[i];
                sp.pop();
            }
            sp.push(i);
        }
        return ans;
    }
};