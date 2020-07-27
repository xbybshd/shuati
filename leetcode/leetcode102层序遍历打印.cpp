/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
public:
    struct node
    {
        TreeNode *tree;
        int depth;
        node(TreeNode *_tree, int _n) : tree(_tree), depth(_n){};
    };
    queue<node> que;
    vector<vector<int>> levelOrder(TreeNode *root)
    {

        vector<vector<int>> va;
        if (root == NULL)
            return va;
        vector<int> vb;
        va.push_back(vb);
        que.push(node(root, 0));
        while (!que.empty())
        {
            node u = que.front();
            que.pop();
            if (va.size() <= u.depth)
            {
                vector<int> vc;
                va.push_back(vc);
            }
            va[u.depth].push_back(u.tree->val);
            if (u.tree->left != NULL)
                que.push(node(u.tree->left, u.depth + 1));
            if (u.tree->right != NULL)
                que.push(node(u.tree->right, u.depth + 1));
        }
        return va;
    }
};