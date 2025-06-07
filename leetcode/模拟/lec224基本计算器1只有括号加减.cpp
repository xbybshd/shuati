class Solution {
public:
    int calculate(string s) {
        std::stack<int> ops;
        ops.push(1);
        int res = 0, num, sign;
        sign = 1;
        int n = s.length();
        // 只有加减的括号，增减括号不改变数值，仅仅是括号内的符号需要替换
        // 如果左括号外贴的括号是-那么内部所有符号都要交换
        // 每次遇到符号时，检查栈顶的符号，这是当前括号外面第一个符号,这里关于正负号是有技巧的，遇到正号，与栈顶符号一样，符号九相反
        // 左括号压住当前符号，右括号就出符号，遇到数值时，当前的sign就是这个数值完全展开的符号，正常计算就行。
        for (int i = 0; i < n;) {
            if (s[i] == ' ') {
                i++;
            }
            else if (s[i] == '+') {
                sign = ops.top();
                i++;
            }
            else if (s[i] == '-') {
                sign = -ops.top();
                i++;
            }
            else if (s[i] == '(') {
                ops.push(sign);
                i++;
            }
            else if (s[i] == ')') {
                ops.pop();
                i++;
            }
            else {
                long num = 0;
                while (i < n && s[i] >= '0' && s[i] <= '9') {
                    num = num * 10 + s[i] - '0';
                    i++;
                }
                res += sign * num;
            }
        }
        return res;
    }
};