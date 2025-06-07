struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x)
        : val(x)
        , left(NULL)
        , right(NULL) {}
};

// 先序遍历
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ans;
        dfs_serialize(root, ans);
        return ans;
    }
    void dfs_serialize(TreeNode* root, std::string& ans) {
        if (root == nullptr) {
            ans += "Null,";
            return;
        }
        ans += std::to_string(root->val) + ",";
        dfs_serialize(root->left, ans);
        dfs_serialize(root->right, ans);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int idx = 0;
        return dfs_deserialize(data, idx);
    }

    TreeNode* dfs_deserialize(std::string& data, int& idx) {
        TreeNode* root = getNode(data, idx);
        if (root != nullptr) {
            root->left = dfs_deserialize(data, idx);
            root->right = dfs_deserialize(data, idx);
        }
        return root;
    }

    TreeNode* getNode(std::string& data, int& idx) {
        int i = idx, val = 0, flag = 1;
        for (; i < data.size(); i++) {
            if (data[i] == 'N') {
                idx += 5;
                return nullptr;
            }
            if (data[i] == ',') {
                break;
            }
            else if (data[i] == '-') {
                flag = -1;
            }
            else {
                val = val * 10 + data[i] - '0';
            }
        }
        idx = i + 1;
        return new TreeNode(flag * val);
    }
};

// 层序遍历
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        std::string ans;
        std::queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            root = que.front();
            que.pop();
            if (root) {
                ans += to_string(root->val) + ",";
                que.push(root->left);
                que.push(root->right);
            }
            else {
                ans += "Null,";
            }
        }
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int idx = 0;
        TreeNode* root = getNode(data, idx);
        std::queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            TreeNode* node = que.front();
            que.pop();
            if (node) {
                node->left = getNode(data, idx);
                if (node->left != nullptr) {
                    que.push(node->left);
                }
                node->right = getNode(data, idx);
                if (node->right) {
                    que.push(node->right);
                }
            }
        }
        return root;
    }

    TreeNode* getNode(std::string& data, int& idx) {
        int i = idx, val = 0, flag = 1;
        for (; i < data.size(); i++) {
            if (data[i] == 'N') {
                idx += 5;
                return nullptr;
            }
            if (data[i] == ',') {
                break;
            }
            else if (data[i] == '-') {
                flag = -1;
            }
            else {
                val = val * 10 + data[i] - '0';
            }
        }
        idx = i + 1;
        return new TreeNode(flag * val);
    }
};