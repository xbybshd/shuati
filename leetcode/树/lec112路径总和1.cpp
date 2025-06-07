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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return false;
        }
        targetSum -= root->val;
        if (targetSum == 0 && root->left == nullptr && root->right == nullptr) {
            return true;
        }
        bool left = false, right = false;
        if (root->left != nullptr)
            left = hasPathSum(root->left, targetSum);
        if (root->right != nullptr)
            right = hasPathSum(root->right, targetSum);
        return left || right;
    }
};