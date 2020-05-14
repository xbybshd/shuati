class Solution {
public:
    int search(vector<int>& nums, int target) {
        int len=nums.size();
        if(len==0) return -1;
        int l,r,mid;
        l=0;
        r=len-1;
        mid=(l+r)>>1;
        while(l<=r){//本题所有都是小于等于
            if(nums[mid]==target) return mid;
            if(nums[l]<=nums[mid]){//先判断最左边是否小于中点mid，小于说明mid左边是正常升序，大于说明mid右边是正常升序
                if(target<=nums[mid]&&target>=nums[l]){//只对正常升序的那一边进行比较target，即最左边
                    r=mid-1;//新lr取值全部都是+1，-1;
                }
                else{
                    l=mid+1;
                }
            }
            else{
                if(target>=nums[mid]&&target<=nums[r]){//与最右边比较target
                    l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            mid=(l+r)>>1;//正常除以2
        }
        return -1;
    }
};