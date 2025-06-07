class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        std::stack<int> sp;
        std::vector<int> ans(temperatures.size(), 0);
        sp.push(0);
        for (int i = 1; i < temperatures.size(); i++) {
            if (temperatures[i] < temperatures[sp.top()]) {
                sp.push(i);
            }
            else {
                int top = sp.top();
                while (!sp.empty() && temperatures[i] > temperatures[sp.top()]) {
                    top = sp.top();
                    ans[top] = i - top;
                    sp.pop();
                }
                sp.push(i);
            }
        }
        return ans;
    }
};

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        std::stack<int> sp;
        std::vector<int> ans(temperatures.size(), 0);
        sp.push(0);
        for (int i = 1; i < temperatures.size(); i++) {
            int top = sp.top();
            // 正常情况下都是入栈，如果当前元素大于栈顶，那就持续出栈，并记录top和当前i距离，单调栈一直是递减栈
            while (!sp.empty() && temperatures[i] > temperatures[sp.top()]) {
                top = sp.top();
                ans[top] = i - top;
                sp.pop();
            }
            sp.push(i);
        }
        return ans;
    }
};