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
    std::unordered_map<int, int> idx;
    TreeNode* dfs(int pre_l, int pre_r, int mid_l, int mid_r, vector<int>& preorder) {
        if (pre_l > pre_r) {
            return nullptr;
        }
        int root = preorder[pre_l];
        int mid_root = idx[root];
        int left_size = mid_root - mid_l;
        TreeNode* left = dfs(pre_l + 1, pre_l + left_size, mid_l, mid_root - 1, preorder);
        TreeNode* right = dfs(pre_l + left_size + 1, pre_r, mid_root + 1, mid_r, preorder);
        return new TreeNode(root, left, right);
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {

        int n = preorder.size();
        for (int i = 0; i < n; i++) {
            idx[inorder[i]] = i;
        }
        return dfs(0, n - 1, 0, n - 1, preorder);
    }
};