/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#define MAX 100010

class Solution
{
public:
    int cnt = 0;
    TreeNode *euler[MAX] = {0};
    int depth[MAX] = {0};
    void dfs(TreeNode *root, int dep)
    {

        if (root->left != NULL)
        {
            dfs(root->left, dep + 1);
            // euler[++cnt]=root;
            // depth[cnt]=dep;
        }
        euler[++cnt] = root; //中序遍历记录节点和深度
        depth[cnt] = dep;
        if (root->right != NULL)
        {
            dfs(root->right, dep + 1);
            // euler[++cnt]=root;
            // depth[cnt]=dep;
        }
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        dfs(root, 1);
        int mindep = 0x3f3f3f3f;
        TreeNode *ans = NULL;
        int ei = 1;
        while (euler[ei] != p && euler[ei] != q)
            ei++; //找到最左边p或q之一
        TreeNode *left = euler[ei];
        TreeNode *right = (euler[ei] == p ? q : p); //把右边界限赋值
        while (euler[ei] != right)
        {
            if (mindep > depth[ei])
            { //找高度最小的点
                mindep = depth[ei];
                ans = euler[ei];
            }
            ei++;
        }
        if (mindep > depth[ei])
        { //最右边还要判断一次
            mindep = depth[ei];
            ans = euler[ei];
        }
        return ans;
    }
};

class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (!root || root == p || root == q)
            return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left && right)
            return root;
        return left ? left : right;
    }
};

// 两个节点 p,q 分为两种情况：

// p 和 q 在相同子树中
// p 和 q 在不同子树中
// 从根节点遍历，递归向左右子树查询节点信息
// 递归终止条件：如果当前节点为空或等于 p 或 q，则返回当前节点

// 递归遍历左右子树，如果左右子树查到节点都不为空，则表明 p 和 q 分别在左右子树中，因此，当前节点即为最近公共祖先；
// 如果左右子树其中一个不为空，则返回非空节点。
