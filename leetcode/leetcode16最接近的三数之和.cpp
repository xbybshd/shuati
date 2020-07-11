class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        long tgt=target;
        long del=LONG_MAX;
        long res=0;
        int len=nums.size();
        for(int i=0;i<len-2;i++){//最左边到len-3为止
            long v=nums[i];
            int l=i+1;
            int r=len-1;//标记好左右
            while(l<r){//左不等于右循环结束
                long v1=nums[l];
                long v2=nums[r];
                if(v+v1+v2==tgt) return tgt;//等于tgt就返回
                if(abs(v+v1+v2-tgt)<del){
                    res=v+v1+v2;//小于差就把差替换掉
                    del=abs(res-tgt);
                }
                if(v+v1+v2<tgt){
                    l++;
                }
                else{
                    r--;
                }
            }
        }
        return res;
    }
};