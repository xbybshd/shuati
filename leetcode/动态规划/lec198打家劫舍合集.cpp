
// 打家劫舍1
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> dp(n, 0);
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                dp[0] = nums[0];
            }
            else if (i == 1) {
                dp[1] = std::max(dp[0], nums[1]);
            }
            else {
                dp[i] = std::max(dp[i - 2] + nums[i], dp[i - 1]);
            }
        }
        return dp[n - 1];
    }
};

class Solution {
public:
    int rob(vector<int>& nums) {
        int dp0 = 0, dp1 = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            int temp = std::max(dp0 + nums[i], dp1);
            dp0 = dp1;
            dp1 = temp;
        }
        return dp1;
    }
};

class Solution {
public:
    int rob(vector<int>& nums) {
        int f0 = 0, f1 = 0;
        for (int x : nums) {
            int new_f = max(f1, f0 + x);
            f0 = f1;
            f1 = new_f;
        }
        return f1;
    }
};

// 打家劫舍2    把1作为包装函数
class Solution {
public:
    int roblinear(int l, int r, std::vector<int>& vec) {
        int dp0 = 0, dp1 = 0;
        for (int i = l; i < r; i++) {
            int temp = std::max(dp1, dp0 + vec[i]);
            dp0 = dp1;
            dp1 = temp;
        }
        return dp1;
    }
    int rob(vector<int>& nums) {
        // 取了0，1和n-1就没法取，只能在2到n-2看环形
        int n = nums.size();
        return std::max(nums[0] + roblinear(2, n - 1, nums), roblinear(1, n, nums));
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// 打家劫舍3树形dp
class Solution {
public:
    std::pair<int, int> dfs(TreeNode* root) {
        if (root == nullptr) {
            return { 0, 0 };
        }
        auto [l0, l1] = dfs(root->left);
        auto [r0, r1] = dfs(root->right);
        int rob = l1 + r1 + root->val;
        int no_rob = std::max(l0, l1) + std::max(r0, r1);
        return { rob, no_rob };
    }
    int rob(TreeNode* root) {
        auto [rob, no_rob] = dfs(root);
        return std::max(rob, no_rob);
    }
};

// 打家劫舍4dp二分，保证偷k家的情况下，最大的偷取某一家nums[i]最小，理论上来说，mx越大，k越大
// mx越小k越小，所以对mx二分，判断条件是偷取次数f1对k的大小
// 如果当前大于mx，
class Solution {
public:
    int rob(int k, int mx, std::vector<int>& nums) {
        int f0 = 0, f1 = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            if (x > mx) {
                f0 = f1; // f1不变，不需要动了
            }
            else {
                int temp = f1;
                f1 = std::max(f0 + 1, f1);
                f0 = temp;
            }
        }
        return f1 >= k;
    }
    int minCapability(vector<int>& nums, int k) {
        int l = 0, r = *max_element(nums.begin(), nums.end());
        while (l < r) {
            int mid = (l + r) >> 1;
            if (rob(k, mid, nums)) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return r;
    }
};