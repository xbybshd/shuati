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
    struct Node {
        TreeNode* ptr;
        int l;
        Node(TreeNode* ptr_, int l_)
            : ptr(ptr_)
            , l(l_) {};
    };
    std::deque<Node> que;
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        que.push_back(Node(root, 0));
        int level = 0;
        std::vector<std::vector<int>> ans;
        if (root == nullptr) {
            return ans;
        }
        ans.push_back(std::vector<int>());
        while (!que.empty()) {
            if (level % 2 == 0) {
                auto& node = que.front();
                ans.back().push_back(node.ptr->val);
                if (node.ptr->left != nullptr)
                    que.push_back(Node(node.ptr->left, level + 1));
                if (node.ptr->right != nullptr)
                    que.push_back(Node(node.ptr->right, level + 1));
                que.pop_front();
                if (que.front().l == level + 1) {
                    level++;
                    ans.push_back(std::vector<int>());
                }
            }
            else {
                auto& node = que.back();
                ans.back().push_back(node.ptr->val);
                if (node.ptr->right != nullptr)
                    que.push_front(Node(node.ptr->right, level + 1));
                if (node.ptr->left != nullptr)
                    que.push_front(Node(node.ptr->left, level + 1));
                que.pop_back();
                if (que.back().l == level + 1) {
                    level++;
                    ans.push_back(std::vector<int>());
                }
            }
        }
        return ans;
    }
};

class Solution {
public:
    std::queue<TreeNode*> que;
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        que.push(root);
        std::vector<std::vector<int>> ans;
        if (root == nullptr) {
            return ans;
        }
        int level = 0;
        while (!que.empty()) {
            std::vector<int> vals;
            for (int i = que.size(); i > 0; i--) {
                TreeNode* node = que.front();
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
                vals.push_back(node->val);
                que.pop();
            }
            if (level % 2 == 1) {
                std::reverse(vals.begin(), vals.end());
            }
            ans.push_back(vals);
            level++;
        }
        return ans;
    }
};