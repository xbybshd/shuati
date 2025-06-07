class Solution {
public:
    int myAtoi(string s) {
        int i = 0, len = s.length(), res = 0, bundry = INT_MAX / 10, sign = 1;
        while (s[i] == ' ') {
            i++;
        }
        if (i == len)
            return 0;
        if (s[i] == '-')
            sign = -1;
        if (s[i] == '-' || s[i] == '+')
            i++;
        for (int j = i; j < len; j++) {
            // 这里只要不在数字范围内，直接停止循环
            if (s[j] < '0' || s[j] > '9') {
                break;
            }
            // bundry是最大int除以十，所以可以提前判断，等于bundry的时候，下一个各位数字大于7就会越界
            if (res > bundry || (res == bundry && s[j] > '7')) {
                return sign == 1 ? INT_MAX : INT_MIN;
            }
            res = res * 10 + (s[j] - '0');
        }
        return sign * res;
    }
};