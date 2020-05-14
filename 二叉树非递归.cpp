#include <bits/stdc++.h>
using namespace std;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {//后序
public:
    stack<TreeNode*> s;
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> v;
        TreeNode* p=root;
        TreeNode* pre=NULL;//起始前节点为空
        if(root==NULL) return v;
        while(p||!s.empty()){//p不为空或栈不为空，因为从下方的节点返回的的时候p会置空
            while(p){
                s.push(p);//一直压入左节点
                p=p->left;
            }
            p=s.top();//取栈顶
            if(p->right==NULL||p->right==pre){//如果右节点为空，或者右节点等于上一次输出的节点
                v.push_back(p->val);//遍历之
                s.pop();//出栈
                pre=p;//前节点pre=p
                p=NULL;//p置空
            }
            else{//否则p为右节点
                p=p->right;
            }       
        }
        return v;
    }
};

class Solution {//前序
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* p=root;
        vector<int> v;
        if(root==NULL) return v;
        while(p||!s.empty()){//p非空，栈非空，因为p为叶子节点的时候while后会指向空的右节点，这个时候需要在循环一次将栈顶赋值给p
            while(p){
                s.push(p);
                v.push_back(p->val);//遍历
                p=p->left;
            }
            p=s.top()->right;//p为栈顶右节点，空的也没关系
            s.pop();//出栈
        }
        return v;
    }
};

class Solution {//中序
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* p=root;
        vector<int> v;
        if(root==NULL) return v;
        while(p||!s.empty()){
            while(p){
                s.push(p);
                p=p->left;
            }
            p=s.top();
            s.pop();
            v.push_back(p->val);
            p=p->right;  
        }
        return v;
    }       
};