class Solution {
public:
    string decodeString(string s) {
        std::string res;
        std::stack<int, std::vector<int>> nums;
        std::stack<std::string, std::vector<std::string>> str;
        int num = 0, n = s.size();
        for (int i = 0; i < n; i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + s[i] - '0';
            }
            else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
                res += s[i];
            }
            else if (s[i] == '[') { // res和num代表从上一个'['开始到当前'['为止的num和字符串
                nums.push(num);
                num = 0;
                str.push(res);
                res = "";
            }
            else {
                int times = nums.top(); // 遇到']'，压入栈的num是对应'['之前的数值，就是当前括号内res的倍数，算完之后要pop
                nums.pop();
                for (int i = 0; i < times; i++) {
                    str.top() += res; // str top指的是'['之前的字符串，当前[]被计算完之后，就是top的字符串
                }
                res = str.top(); // 当前[]被计算完毕，res就代表外层的str了，
                str.pop(); // [str.top[]]已经计算完毕，不需要
            }
        }
        return res;
    }
};