class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int len=strs.size();
        if(len==0) return string("\0");
        int len1=strs[0].length();
        for(int i=0;i<len1;i++){
            char ec=strs[0][i];
            for(int j=1;j<len;j++){
                if(strs[j][i]!=ec){
                    string ans(strs[0],0,i);//将字符串str[0]从零开始，一共i个字符赋值给ans
                    return ans;
                }
            }
            
        }
        return strs[0];
    }
};