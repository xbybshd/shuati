class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len=nums.size();
        int maxn=0x80000000;
   
        int pre=0;
        int now=0;
        for(int i=0;i<len;i++){
            now=max(pre+nums[i],nums[i]);//到前一个为止的最大和加上当前值如果小于当前值，就直接放弃，从当前值开始
            pre=now;//保存当前最大值
            maxn=max(maxn,now);//取最大值
        }
        return maxn;
    }
};