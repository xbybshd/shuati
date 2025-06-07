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
    bool isCompleteTree(TreeNode* root) {
        std::queue<TreeNode*> que;
        que.push(root);
        int meet_null = 0;
        while (!que.empty()) {
            TreeNode* u = que.front();
            que.pop();
            if (u == nullptr) {
                meet_null = 1;
                continue;
            }
            else {
                if (meet_null == 1) {
                    return false;
                }
                que.push(u->left);
                que.push(u->right);
            }
        }
        return true;
    }
};