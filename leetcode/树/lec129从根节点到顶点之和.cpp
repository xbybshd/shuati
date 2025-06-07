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
    int ans = 0;
    void dfs(TreeNode* root, int x) {
        if (root == nullptr) {
            return;
        }
        x = x * 10 + root->val; // 先序遍历，和从顶点沿着路径一路传下去，美传1层，原和乘上10加上当前节点值
        if (root->left == root->right) {
            ans += x; //叶子节点将路径和加到总和上
            return;
        }
        dfs(root->left, x);
        dfs(root->right, x);
    }
    int sumNumbers(TreeNode* root) {
        dfs(root, 0);
        return ans;
    }
};