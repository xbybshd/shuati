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


class Solution {
public:
    int cnt=0;
    TreeNode* euler[MAX]={0};
    int depth[MAX]={0};
    void dfs(TreeNode* root,int dep){//根节点，当前深度
        euler[++cnt]=root;//欧拉序数组，存入根节点
        depth[cnt]=dep;//欧拉序数组的对应深度数组
        if(root->left!=NULL){
            dfs(root->left,dep+1);//深度加1
            euler[++cnt]=root;//返回的时候再存入一次根节点
            depth[cnt]=dep;
        }
        if(root->right!=NULL){
            dfs(root->right,dep+1);
            euler[++cnt]=root;
            depth[cnt]=dep;
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root,1);//先建立欧拉序数组和深度数组
        int mindep=0x3f3f3f3f;
        TreeNode* ans=NULL;
        int ei=1;
        while(euler[ei]!=p&&euler[ei]!=q) ei++;//找到最左端的p或q
        TreeNode* left=euler[ei];//将其赋值给left
        TreeNode* right=(euler[ei]==p?q:p);//那么right就是右边的
        while(euler[ei]!=right){//在找到右边的数之前
            if(mindep>depth[ei]){
                mindep=depth[ei];//深度最小的节点就是LCA
                ans=euler[ei];
            }
            ei++;
        }
        return ans;
    }
};