class Solution {
public:
    void rota(vector<int>&nums,int li,int ri){
        int len1=ri-li+1;
        int len2=li+(len1>>1);
        for(int i=li;i<len2;i++){
            swap(nums[i],nums[ri-(i-li)]);
        }
    }
    void rotate(vector<int>& nums, int k) {
        if(k==0) return;
        int len=nums.size();
        k=k%len;
        rota(nums,0,len-1);//总翻转一次
        rota(nums,0,k-1);//0-k-1翻转一次
        rota(nums,k,len-1);//k-1--len-1翻转一次
        return;
    }
};