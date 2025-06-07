class Solution {
public:
    int calculate(string s) {
        std::vector<int> sp;
        char sign = '+';
        int n = s.length();
        int num = 0;
        // 三种基本情况，空格，符号，数字，遇到数字先处理数字，之后不是空格，不是数字，就是符号
        // 注意此时遇到的是新的符号，同时上一个表达式的最后数字也处理完毕，应该处理上个表达式的最后数字。处理完后记录新的符号，将数字设为0
        // 在最后，因为只有新符号到达的时候，才会处理上一个符号和数字，但是字符串结尾没有新的符号，所以只能把字符串最后一个有意义字符，也当作标志
        // 第一个符号默认是+，其实并不是真实的，仅仅是占位，负责将第一个数压进去
        for (int i = 0; i < n; i++) {
            if (isdigit(s[i])) {
                num = num * 10 + int(s[i] - '0');
            }
            if (!isdigit(s[i]) && s[i] != ' ' || i == n - 1) {
                if (sign == '+') {
                    sp.push_back(num);
                }
                else if (sign == '-') {
                    sp.push_back(-num);
                }
                else if (sign == '*') {
                    sp.back() *= num;
                }
                else {
                    sp.back() /= num;
                }
                sign = s[i];
                num = 0;
            }
        }
        return std::accumulate(sp.begin(), sp.end(), 0);
    }
};

// 滞后形式的处理，我当前拿到的数据不立刻处理，处理的是上一次的，当前的数据只是触发，这种方式需要一个前置占位和一个最后结尾标记