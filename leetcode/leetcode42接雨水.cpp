class Solution {
public:
    vector<int> lscan;
    int trap(vector<int>& height) {
        if (height.empty() || height.size() == 1)
            return 0;
        int lm = height[0];
        lscan.push_back(height[0]); //左向扫描，初始化第一个
        int len = height.size();
        int sum1 = height[0];
        for (int i = 1; i < len; i++) {
            sum1 += height[i];
            if (height[i] > lm) {
                lm = height[i]; //只加入最大的
                lscan.push_back(height[i]);
            }
            else {
                lscan.push_back(lm);
            }
        }
        int rm = height[len - 1];
        int all = 0;
        for (int i = len - 1; i >= 0; i--) {
            int nowr;
            if (height[i] > rm) {
                rm = height[i];
            }
            all += min(rm, lscan[i]);
        }
        int v = all - sum1;
        return v;
    }
};

class Solution {
public:
    int trap(vector<int>& height) {
        int pre_max = 0, suf_max = 0, ans = 0, left = 0, right = height.size() - 1;
        while (left < right) {
            // 对于当前i来说，其高度必然小于pre_max或者right_max,之后比较premax和sufmax，找他们的最小值，这样某一边的height
            // 必然小于两边 premax，sufmax，只要出现两边高，那就必然中间会存水，数组就低的那一边高的，减去当前。
            // 之后就是谁小更新谁
            pre_max = std::max(pre_max, height[left]);
            suf_max = std::max(suf_max, height[right]);
            ans += pre_max < suf_max ? pre_max - height[left++] : suf_max - height[right--];
        }
        return ans;
    }
};

class Solution {
public:
    int trap(vector<int>& height) {
        int l = 0, r = 0;
        int ans = 0;
        std::stack<int> sp;
        for (int i = 0; i < height.size(); i++) {
            // 这种方法的关键在于，栈里面一定是一个单调减的，当新元素大于栈顶的时候，第二top的元素一定大于栈顶
            // 这样就组成了一个凹槽，可以计算一次储水量，但是这里记录的是位置而不是具体高度，因为这是按照行来计算的，可能
            // 两端跨有了多个列
            // 当当前i大于栈顶，先记录栈顶，此为凹槽底部，pop如果此时栈空，说明没有凹槽左边缘，那就不进行后续
            // 之后获取新的栈顶，即左边缘，
            while (!sp.empty() && height[i] > height[sp.top()]) {
                int bottom = height[sp.top()];
                sp.pop();
                if (!sp.empty()) {
                    int left = sp.top();
                    int up = std::min(height[left], height[i]);
                    ans += (up - bottom) * (i - left - 1);
                }
            }
            sp.push(i);
        }
        return ans;
    }
};