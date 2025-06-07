// 动态规划解法
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size(), max_len = 0, ans = 0;
        std::vector<int> dp(n), cnt(n);
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
            cnt[i] = 1;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    if (dp[i] < dp[j] + 1) {
                        dp[i] = dp[j] + 1;
                        cnt[i] = cnt[j];
                    }
                    else if (dp[i] == dp[j] + 1) {
                        cnt[i] += cnt[j];
                    }
                }
            }
            if (dp[i] > max_len) {
                max_len = dp[i];
                ans = cnt[i];
            }
            else if (dp[i] == max_len) {
                ans += cnt[i];
            }
        }
        return ans;
    }
};

// 二分查找
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        std::vector<std::vector<int>> seq, cnt;
        for (int u : nums) {
            int in_pos = 1, seq_num = 1;
            if (seq.size() == 0 || u > seq.back().back()) {
                in_pos = seq.size();
            }
            else {
                in_pos = std::lower_bound(seq.begin(), seq.end(), u, [](const std::vector<int>& a, int b) {
                    return a.back() < b;
                }) - seq.begin();
            }
            if (in_pos > 0) {
                int pre_pos = in_pos - 1;
                int pre_num_pos = std::upper_bound(seq[pre_pos].begin(), seq[pre_pos].end(), u, std::greater<int>()) - seq[pre_pos].begin();
                seq_num = cnt[pre_pos].back() - (pre_num_pos ? cnt[pre_pos][pre_num_pos - 1] : 0);
            }
            if (in_pos == seq.size()) {
                seq.push_back({ u });
                cnt.push_back({ seq_num });
            }
            else {
                seq[in_pos].push_back(u);
                cnt[in_pos].push_back(cnt[in_pos].back() + seq_num);
            }
        }
        return cnt.size() ? cnt.back().back() : 0;
    }
};

// seq[][]  第一维度是序列长度，第二维度是当前长度的结尾序列数字，是按照降序排列
// 两次查找，先二分查找每个长度的数组的末尾数字，这个数字是升序排列，查找到第一个末位数大于等于当前数的数组，插入这个数组末尾，
// 理论上是因为当当前数大于前一个长度的末尾数，就可以与前一个长度的某几个数构成+1长度的递增数组

// cnt[][]是与seq对应的，末尾值大于等于当前数，并且长度一样的序列数量，首先需要对seq的插入位置数组前一个数组进行二分查找，
// 二次查找的数组是降序排列，用lower_bound，greater,是查找第一个小于当前数的位置，代表当前数可以接在这个位置后面形成LIS，这个数的前一个
// 位置的cnt，代表完全不能与当前数构成LIS的数量，所以用当前cnt[].back()-cnt[pos-1]得刚好小于当前数的前一个位置的LIS数量，再加上插入
// 位置的末尾cnt数量，相当于比他大的LIS数量。本质上是以当前数结尾的num+大于当前数位结尾的num；
// https: //leetcode.cn/problems/number-of-longest-increasing-subsequence/solutions/153672/yi-bu-yi-bu-tui-dao-chu-zui-you-jie-fa-2-zui-chang/