class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1, ans = 0, max_ans = 0;
        while (l < r) {
            // 核心思想，移动大的一边，间距变小，但是高度受到短板制约，依然不变，所以没有办法移动大的
            // 每次移动相当于剪枝
            ans = std::min(height[l], height[r]) * (r - l);
            max_ans = std::max(ans, max_ans);
            height[l] < height[r] ? l++ : r--;
        }
        return max_ans;
    }
};