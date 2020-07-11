class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > ans;
        int len=nums.size();
        sort(nums.begin(),nums.end());
        for(int i=0;i<len-2;i++){//i最大为倒数第三个数
            if(i==0||(i>0&&nums[i]!=nums[i-1])){//涉及到i-1，分i=0，和i>0来考虑，当前i与前一个i相同的时候跳过
                int low=i+1;//low为i的后一个
                int high=len-1;//每前进一个i,high都要从最后面一个开始
                while(low<high){
                    if(nums[low]+nums[high]>-nums[i]){//三个加起来大于0，high--
                        high--;
                    }
                    else if(nums[low]+nums[high]<-nums[i]){//三个加起来小于0，low++
                        low++;
                    }
                    else{
                        int prelow=nums[low];
                        int prehigh=nums[high];
                        vector<int> elem{nums[i],prelow,prehigh};
                        ans.push_back(elem);//否则就将三元组存入ans
                        while(prelow==nums[low]&&low<high) low++;//low如果等于下一个，在low小于high之前，将low++
                    }
                }
            }
        }
        return ans;
    }
};