class Solution {
public:
    struct Node {
        TreeNode* ptr;
        int level;
        Node(TreeNode* node_ptr, int lev)
            : ptr(node_ptr)
            , level(lev) {};
    };
    vector<vector<int>> levelOrder(TreeNode* root) {
        std::queue<Node> que;
        std::vector<std::vector<int>> ans;
        if (root == nullptr) {
            return ans;
        }
        que.push(Node(root, 0));
        while (!que.empty()) {
            Node u = que.front();
            que.pop();
            if (ans.size() <= u.level) {
                ans.push_back(std::vector<int>());
            }
            ans[u.level].push_back(u.ptr->val);
            if (u.ptr->left != nullptr)
                que.push(Node(u.ptr->left, u.level + 1));
            if (u.ptr->right != nullptr)
                que.push(Node(u.ptr->right, u.level + 1));
        }
        return ans;
    }
};