class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        int res = 1, pre = 1, dec = 0, inc = 1;
        // res是答案，pre是记录递增序列长度，也是递增序列当前的分发数值，dec是记录当前下降序列的长度，也是当前的分发数值
        // inc是递增序列长度，用来记录，在递减序列时进行比较
        for (int i = 1; i < n; i++) {
            if (ratings[i] >= ratings[i - 1]) {
                dec = 0;
                pre = ratings[i] == ratings[i - 1] ? 1 : pre + 1; // 递增序列时，如果出现前后相等，后面的直接设为1
                // 如果疑问后面出现大量递减，1兜不住怎么办，这些在递减的时候会处理
                res += pre; // 结果就是加上pre
                inc = pre;
            }
            else {
                dec++; // dec进来的时候就是1
                if (inc == dec) {
                    dec++; // 核心逻辑，计算递减序列的时候，并不是从顶端从大到小计算，而是遍历从大到小，但是计算从小到大反过来逆转
                    // 因为从小到大是从1开始，如果递减序列长度小于递增序列，那么1加到长度dec不会超过顶峰
                    // 如果递减序列超过了，相当于递增的顶峰兜不住了，解决方法把递增顶峰算在递减序列内，直接加高递增顶峰即可，
                    // 如果递减继续增加，相当于递减顶峰向前移动，然后添上新的顶峰
                }
                res += dec;
                pre = 1;
            }
        }
        return res;
    }
};