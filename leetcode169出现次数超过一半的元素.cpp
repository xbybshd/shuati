class Solution {
    public int majorityElement(int[] nums) {
        int vote = 0;   int target = nums[0];
        for(int i =0;i<nums.length;i++){
            if(nums[i]==target) vote++;
            if(nums[i]!=target) vote--;
            if(vote==0&&(i+1)<nums.length) target=nums[i+1];
        }
        return target;
    }
}
