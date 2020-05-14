class Solution {
public:
    deque<int> que;
    int lengthOfLongestSubstring(string s) {
        int lens=s.length();
        int has[130]={0};//ascii码的哈希
        char c;
        int len=0;
        int maxlen=0;
        for(int i=0;i<lens;i++){
            c=s[i];
            if(has[c]){//当前窗口内有当前的字符
                while(!que.empty()&&que.front()!=c) {
                    has[que.front()]=0;//从左边队头开始，不等于当前字符的都出队，哈希置为0
                    que.pop_front();//出队
                    len--;//队的长度--
                }
                if(!que.empty()){//把当前重复字符出队
                    has[que.front()]=0;
                    que.pop_front();
                    len--;
                }
            }
           
                que.push_back(c);//压入当前字符
                has[c]=1;//哈希置为1
                len++;
            
            maxlen=max(len,maxlen);
        }
        return maxlen;
    }
};