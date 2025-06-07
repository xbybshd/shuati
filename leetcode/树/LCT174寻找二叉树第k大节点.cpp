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
    int res, cnt;
    void dfs(TreeNode* root) {
        if (root == nullptr)
            return;
        dfs(root->right);
        if (cnt == 0) // 这里不是为了找到而返回，而是当后面已经找到斌不过记录数值的时候，其他的dfs分支立刻提前终止。
            return;
        if (--cnt == 0)
            res = root->val;
        dfs(root->left);
    }

    int findTargetNode(TreeNode* root, int cnt) {
        this->cnt = cnt;
        dfs(root);
        return res;
    }
};