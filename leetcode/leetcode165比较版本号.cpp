class Solution {
public:
    vector<int> process(string& s){
        int len = s.length();
        int i=0;
        int j=0;
        vector<int> v1;
        bool is_all_zero=true;
        while(j<=len){
            while(s[j]!='.'&&j!=len){
                if(s[j]!='0'&&is_all_zero){
                    i=j;
                    is_all_zero=false;
                }
                j++;
            }
            if(is_all_zero) i=j-1;
            string sub1=s.substr(i,j-i);
            //cout<<sub1<<"\n";
            v1.push_back(stoi(sub1));
            j++;
            is_all_zero=true;
        }
        return v1;
    }
    int compareVersion(string version1, string version2) {
        vector<int> v1=process(version1);
        //cout<<v1<<"\n\n";
        vector<int> v2=process(version2);
        //cout<<v2<<"\n";
        int l1=v1.size();
        int l2=v2.size();
        int l3=l1>l2?l2:l1;
        int l4=l1>l2?l1:l2;
        vector<int> &small = l1>l2?v2:v1;
        for(int i=0;i<l4-l3;i++){
            small.push_back(0);
        }
        for(int i=0;i<l4;i++){
            if(v1[i]>v2[i]){
                return 1;
            }
            else if(v1[i]<v2[i]){
                return -1;
            }
        }
        //if(l1!=l2) return l1>l2?1:-1;
        return 0;
    }
};



class Solution {
public:
    int compareVersion(string s1, string s2) {
        int i=0,j=0;
        while(i<s1.size()||j<s2.size())
        {
            int x=i,y=j;
            while(x<s1.size()&&s1[x]!='.') x++;
            while(y<s2.size()&&s2[y]!='.') y++;
            int a = (i==x)?0:atoi(s1.substr(i,x-i).c_str());
            int b = (j==y)?0:atoi(s2.substr(j,y-j).c_str());
            if(a>b) return 1;
            else if(a<b) return -1;
            i=x+1;j=y+1;
        }
        return 0;
    }
};
