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
    bool recur(TreeNode* A, TreeNode* B) {
        if (B == nullptr) { // B是空节点，说明B已经到了底部，A无论是什么数值都包含B，并且由于判断顺序，A不可能在B之前为空
            return true;
        }
        if (A == nullptr || A->val != B->val) { // B不为空A为空的时候判定失败，或者AB数值不相同
            return false;
        }
        return recur(A->left, B->left) && recur(A->right, B->right);
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        // 两个都不能是空的，且   A，B根节点相同，B是子结构  或者  B在A的某个左右子树根节点相同是子结构
        return (A != nullptr && B != nullptr) && (recur(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B));
    }
};