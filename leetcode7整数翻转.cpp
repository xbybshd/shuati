class Solution {
public:
    int reverse(int x) {
        long long ans=0;
        long max=0x7fffffff;
        while(x){
            ans*=10;
            ans+=x%10;
            cout<<ans<<endl;
            x/=10;
        }
        if(ans>max||ans<(-1*(max+1))){
            ans=0;
        }
        return ans;
      
    }
};