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
    vector<int> path;
    void dfs(vector<vector<int>>& ans, TreeNode* root, int targetSum, int now_sum) {
        now_sum = root->val + now_sum;

        if (now_sum == targetSum) {
            // if(root->left!=nullptr || root->right!=nullptr){
            //     return;
            // }
            if (root->left == nullptr && root->right == nullptr) {
                ans.emplace_back(path);
                return;
            }
        }
        if (root->left != nullptr) {
            path.emplace_back(root->left->val);
            dfs(ans, root->left, targetSum, now_sum);
            path.pop_back();
        }
        if (root->right != nullptr) {
            path.emplace_back(root->right->val);
            dfs(ans, root->right, targetSum, now_sum);
            path.pop_back();
        }
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        if (root == nullptr) {
            return ans;
        }
        path.push_back(root->val);
        dfs(ans, root, targetSum, 0);
        return ans;
    }
};

class Solution {
public:
    vector<int> path;
    void dfs(vector<vector<int>>& ans, TreeNode* root, int left) {
        if (root == nullptr) {
            return;
        }
        path.push_back(root->val);
        left -= root->val;
        if (root->left == root->right && left == 0) {
            ans.push_back(path);
        }
        else {
            dfs(ans, root->left, left);
            dfs(ans, root->right, left);
        }
        path.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        if (root == nullptr) {
            return ans;
        }
        dfs(ans, root, targetSum);
        return ans;
    }
};