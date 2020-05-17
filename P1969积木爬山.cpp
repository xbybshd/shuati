#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 5002
#define INF 0x80000000
#define MAXF 0x3f3f3f3f
int n, m, r,c;
int sx, sy;
int u, v;
int cal[MAX] = {0};
int dp[MAX] = {0};
int fan[MAX] = {0};



int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);
    int pre=0;
    
    
    fcin>>n;
    fcin>>pre;
    int ans=pre;
    int p=pre;
    for(int i=1;i<n;i++){
        fcin>>r;
        if(r>pre&&r>p){
           ans+=r-p;
        }
        else if(r<p){
            pre=r;
        }
        p=r;
        
    }

    fcout<<ans;

    fcin.close();
    fcout.close();

        return 0;
}