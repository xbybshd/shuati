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
    std::unordered_map<long long, int> cnt { { 0, 1 } };
    int max_ans = 0;
    void dfs(TreeNode* root, int targetSum, long long sum) {
        if (root == nullptr) {
            return;
        }
        sum += root->val;
        // 这里cut代表的是，从根节点到当前节点的路径上，长度s的路径于数量的对应关系，不算其他节点遍历的结果
        // 意思是先记录下每步经过的距离，记录长了之后，会出现  前面一段+tragetsm=当前距离的情况，因为数值是离散的，所以会有不同的情况，需要每次判断
        max_ans += cnt.contains(sum - targetSum) ? cnt[sum - targetSum] : 0;
        // 向下遍历前后恢复现场，说明仅限于当前路径
        cnt[sum]++;
        dfs(root->left, targetSum, sum);
        dfs(root->right, targetSum, sum);
        cnt[sum]--;
    }
    int pathSum(TreeNode* root, int targetSum) {
        dfs(root, targetSum, 0);
        return max_ans;
    }
};