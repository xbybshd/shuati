class Solution {
public:
    int findNthDigit(int n) {
        long start = 1, digit = 1, count = 9;
        // 题目的下标是从1开始的，所以每一层的第一个减去之前所有什么层数的n值是1，所以计算属于哪一个数时需要-1，因为1，2，3会导致3与1，2不一起
        while (n > count) {
            n -= count; // 减去每层的数量
            start *= 10; // 每个子树的数量
            digit += 1; // 每一层的数据位数，100就是三位数，n是总位数
            count = digit * start * 9;
        }
        long num = start + (n - 1) / digit; // 就是基本的起始减去第几个格子，算出此时的具体数字
        return std::to_string(num)[(n - 1) % digit] - '0'; // 具体数字转化为字符串，然后取其中一位
    }
};