class Solution {
public:
    int search(vector<int>& nums, int target) {
        int len = nums.size();
        if (len == 0)
            return -1;
        int l, r, mid;
        l = 0;
        r = len - 1;
        mid = (l + r) >> 1; //  串联细节，r，l取准确数组下标，mid直接右移位运算
        while (l <= r) { //本题所有都是小于等于，lr的终结条件是等于，就必须三分，且更新都是+1，-1‘
            if (nums[mid] == target)
                return mid;
            if (nums[l] <= nums[mid]) { //先判断最左边是否小于中点mid，小于说明mid左边是正常升序，大于说明mid右边是正常升序
                if (target <= nums[mid] && target >= nums[l]) { //只对正常升序的那一边进行比较target，即最左边
                    r = mid - 1; //新lr取值全部都是+1，-1;
                }
                else {
                    l = mid + 1;
                }
            }
            else {
                if (target >= nums[mid] && target <= nums[r]) { //与最右边比较target
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
            mid = (l + r) >> 1; //正常除以2
        }
        return -1;
    }
};

// 只有在左右之间是连续德情况下，才可以讨论进入下一步二分，所以先判断中点跟左区间连续还是右区间连续
// 进入连续区间之后，判断target是在不在连续区间，在就继续进入，后续都是正常二分
// 不在就在非连续区间，这种就转换成了新的非连续区间问题，只不过范围缩小了
// 最坏的情况下，traget是最大的处于中间的那个点，会一直进入非连续区间，最后区间大小变为1，得到结果