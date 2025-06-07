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
    std::vector<int> rlist, slist;
    const int lnull = 0x3f3f3f3f;
    const int rnull = 0x80000000;
    void dfs(TreeNode* root, std::vector<int>& path) {
        if (root == nullptr) {
            return;
        }
        path.push_back(root->val);
        if (root->left != nullptr) {
            dfs(root->left, path);
        }
        else {
            path.push_back(lnull);
        }
        if (root->right != nullptr) {
            dfs(root->right, path);
        }
        else {
            path.push_back(rnull);
        }
    }
    bool kmp(std::vector<int>& l1, std::vector<int>& l2) {
        std::vector<int> next(l2.size(), -1);
        // 模板的kmp，序列都是从下标1开始，j从0
        // 在这里是vector可以从0开始，则i从1，j从-1，-1的意义是此时i已经不能不动了，i+1然后j从零开始，j为0的意思是i不动，j到0
        // 因为0之后的-1是有意义的，所以必须要从-1开始，所以判断条件是i==j+1
        for (int i = 1, j = -1; i < l2.size(); i++) {
            while (j != -1 && l2[i] != l2[j + 1]) {
                j = next[j];
            }
            if (l2[i] == l2[j + 1]) {
                j++;
            }
            next[i] = j;
        }
        for (int i = 0, j = -1; i < l1.size(); i++) {
            while (j != -1 && l1[i] != l2[j + 1]) {
                j = next[j];
            }
            if (l1[i] == l2[j + 1]) {
                j++;
            }
            if (j == l2.size() - 1) {
                return true;
            }
        }
        return false;
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        dfs(root, rlist);
        dfs(subRoot, slist);
        bool ans = kmp(rlist, slist);
        return ans;
    }
};