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
    TreeNode* dfs(int ml, int mr, int pl, int pr, vector<int>& inorder, vector<int>& postorder) {
        if (pl > pr) {
            return nullptr;
        }
        int val = postorder[pr];
        int mid = idx[val];
        int len = mid - ml;
        TreeNode* left = dfs(ml, mid - 1, pl, pl + len - 1, inorder, postorder);
        TreeNode* right = dfs(mid + 1, mr, pl + len, pr - 1, inorder, postorder);
        return new TreeNode(val, left, right);
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        for (int i = 0; i < n; i++) {
            idx[inorder[i]] = i;
        }
        TreeNode* root = dfs(0, n - 1, 0, n - 1, inorder, postorder);
        return root;
    }
};