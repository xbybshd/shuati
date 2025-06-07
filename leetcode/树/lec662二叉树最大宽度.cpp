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
    using ull = unsigned long long;
    int widthOfBinaryTree(TreeNode* root) {
        ull res = 1;
        std::vector<std::pair<TreeNode*, ull>> que;
        que.emplace_back(root, 1L);
        while (!que.empty()) {
            auto& [node1, idx1] = que[0];
            auto& [node2, idx2] = que.back();
            res = std::max(res, idx2 - idx1 + 1);
            std::vector<std::pair<TreeNode*, ull>> tmp;
            for (auto& [node, idx] : que) {
                if (node->left != nullptr)
                    tmp.emplace_back(node->left, idx * 2);
                if (node->right != nullptr)
                    tmp.emplace_back(node->right, idx * 2 + 1);
            }
            que = std::move(tmp);
        }
        return res;
    }
};