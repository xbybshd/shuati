class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        std::stack<int, std::vector<int>> sp;
        sp.push(-1); // 需要一个最左边
        heights.push_back(0); // 需要一个最右边
        int ans = 0;
        for (int i = 0; i < heights.size(); i++) {
            // 这里最左边不能进行比较，因为是-1,所以栈不空的条件变成保留一个元素
            while (sp.size() > 1 && heights[sp.top()] > heights[i]) {
                int high = heights[sp.top()]; // 当前top只是高度
                sp.pop();
                int left = sp.top() + 1; // 实际的左边是下一个top+1，因为会有中间一大堆被弹出了，但是计算还是要算的
                int right = i;
                ans = std::max(ans, high * (right - left));
            }
            sp.push(i);
        }
        return ans;
    }
};