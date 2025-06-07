class Solution {
public:
    int maximumSwap(int num) {
        std::string s = std::to_string(num);
        int n = s.length();
        int max_pos = n - 1, max_elem = 0, pos = -1, c_pos = -1;
        for (int i = n - 2; i >= 0; i--) {
            if (s[i] > s[max_pos]) { // 最大位置从n-1开始。所以遍历从n-2,记录最大
                max_pos = i;
            }
            else if (s[i] < s[max_pos]) { // 当遇到小于最大的时候，记录此时最大最小，按照这个来交换，因为最大值会更新
                // 比如最大值在首位的情况，就不能交换
                pos = i;
                c_pos = max_pos;
            }
        }
        if (pos == -1) {
            return num;
        }
        swap(s[pos], s[c_pos]);
        return stoi(s);
    }
};