class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int mx = 0;
        for (int i = 0; i < n; i++) {
            if (i > mx) {
                return false;
            } // 每次记录自己可以到达的最大位置
            mx = std::max(mx, i + nums[i]);
        }
        return true;
    }
};

class Solution {
public:
    int jump(vector<int>& nums) {
        int next_step = 0, cur_step = 0, ans = 0;
        // 先得到当前可以达到的最大位置，然后慢慢走，每步都探测从当前位置开始时的最大位置，如果到头了，相当于开始那一步不是走到头
        // 而是直接到达探测的可以达到最大位置中的某一步，相当于走回头路，但是这个位置其实不需要走回头路
        for (int i = 0; i + 1 < nums.size(); i++) {
            next_step = std::max(next_step, i + nums[i]);
            if (i == cur_step) {
                cur_step = next_step;
                ans++;
            }
        }
        return ans;
    }
};