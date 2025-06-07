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
    void preorder(TreeNode* root, int depth, std::vector<int>& ans) {
        if (root == nullptr) {
            return;
        }
        if (depth == ans.size()) {
            ans.push_back(root->val);
        }
        else {
            ans[depth] = root->val;
        }
        preorder(root->left, depth + 1, ans);
        preorder(root->right, depth + 1, ans);
    }
    vector<int> rightSideView(TreeNode* root) {
        std::vector<int> ans;
        if (root == nullptr)
            return ans;
        preorder(root, 0, ans);
        return ans;
    }
};