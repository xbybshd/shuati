class Solution {
public:
#define MAX 1000
char s[MAX];
char s0[2 * MAX + 10];
int p[2 * MAX + 10] = {0};
    string longestPalindrome(string s) {
        int len=s.length();
        int j=2;
        s0[0]='$';
        s0[1]='#';
        for(int i=0;i<len;i++){//变成$#a#a#b#a的类型
            s0[j++]=s[i];
            s0[j++]='#';
        }
        int len1=j;
        int mid=0;//中点枢轴
        int maxr=0;//最大右端点
        int ans=1;//如果要返回具体字符串，可选最大长度
        int maxi=2;//如果要返回具体字符串，可选最大长度时的位置
        for(int i=1;i<=len1;i++){
            if(i<=maxr)//当前i在最大右端点左边
                p[i]=min(p[(mid<<1)-i],maxr-i);//可以通过对称性找到相对于mid的对称点j，取j的长度和最大右端点减i
            while(s0[i+p[i]+1]==s0[i-p[i]-1]) ++p[i];//开始两边拓展
            if(i+p[i]>maxr){
                maxr=i+p[i];//更新右端点和枢轴
                mid=i;
            }
            if(p[i]>ans){
                ans=p[i];//更新最大
                maxi=i;
            }  
        }
        if(maxi==1){
            maxi=2;//如果最大是第一个将其调整为第二个实体字符
            p[maxi]=0;
        }
        string ansstr;
        int l=maxi-p[maxi];
        int r=maxi+p[maxi];
        for(int i=l;i<=r;i++){
            if(s0[i]!='#'&&s0[i]!='$')
                ansstr.insert(ansstr.end(),s0[i]);
        }
        return ansstr;
    }
};