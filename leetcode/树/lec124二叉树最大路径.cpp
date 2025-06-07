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
class Solution {
public:
    int max_ans = 0x80000000;
    int dfs(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int left_sum = dfs(root->left);
        int right_sum = dfs(root->right);
        int val = root->val;
        int now_sum = val;
        now_sum += left_sum > 0 ? left_sum : 0;
        now_sum += right_sum > 0 ? right_sum : 0;
        max_ans = std::max(max_ans, now_sum);
        int res_sum = std::max(val, std::max(val + left_sum, val + right_sum));
        return res_sum;
    }
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return max_ans;
    }
};