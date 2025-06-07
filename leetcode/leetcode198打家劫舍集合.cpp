class Solution1 { //线性数组
public:
#define MAX 10000
    int dp[MAX] = { 0 };
    int rob(vector<int>& nums) {
        if (nums.empty())
            return 0;
        int l1 = nums.size();
        for (int i = 0; i < l1; i++) {
            if (i == 0)
                dp[i] = nums[i];
            else if (i == 1)
                dp[i] = max(nums[i], nums[i - 1]);
            else
                dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[l1 - 1];
    }
};

class Solution2 { //环形数组
public:
#define MAX 100000
    int dp[MAX] = { 0 };
    int scan(int l, int r, vector<int>& nums) {
        int len = r - l; //分项长度
        if (len == 0)
            return nums[l]; //分项长度为空
        dp[l] = nums[l];
        if (len == 1)
            return max(nums[0], nums[1]); //分项长度为1
        for (int i = l; i <= r; i++) {
            if (i == l)
                dp[i] = nums[i]; //分项长度大于2是,第1项和第2项要单独考虑
            else if (i == l + 1)
                dp[i] = max(nums[i], nums[i - 1]);
            else
                dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[r];
    }
    int rob(vector<int>& nums) {
        if (nums.empty())
            return 0; //总体为空
        int l1 = nums.size();
        if (l1 == 1)
            return nums[0]; //总体为1
        int ans1 = scan(0, l1 - 2, nums);
        int ans2 = scan(1, l1 - 1, nums);
        return max(ans1, ans2);
    }
};

class Solution3 { //树形dp，类似没有上司的舞会
public:
#define MAX 10000
    int dp[MAX][2] = { 0 };
    int cnt = -1;
    int dfs(TreeNode* root) {
        ++cnt;
        int ni = cnt;
        dp[ni][1] += root->val;
        if (root->left != NULL) {
            int lni = dfs(root->left);
            dp[ni][1] += dp[lni][0];
            dp[ni][0] += max(dp[lni][0], dp[lni][1]);
        }
        if (root->right != NULL) {
            int rni = dfs(root->right);
            dp[ni][1] += dp[rni][0];
            dp[ni][0] += max(dp[rni][0], dp[rni][1]);
        }
        return ni;
    }
    int rob(TreeNode* root) {
        if (root == NULL)
            return 0;
        int r = dfs(root);
        return max(dp[r][0], dp[r][1]);
    }
};