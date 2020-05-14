/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
int ans=0;//开一个全局变量
    int diameterOfBinaryTree(TreeNode* root) {
        depth(root);
        return ans; 
    }
    int depth(TreeNode* root){
        if(root==NULL) return 0;
        int left=depth(root->left);
        int right=depth(root->right);
        ans=max(left+right,ans);//与全局比较
        return max(left,right)+1;//每个递归返回的是自己的左右分支中较大的一个
    }
};