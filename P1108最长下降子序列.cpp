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

    fcin >> n;
    for (int i = 0; i < n;i++){
        fcin >> cal[i];
    }
    int maxn = 0;
    for (int i = 0; i < n;i++){
        dp[i] = 1;
        for (int j = i; j >= 0;j--){
            if(cal[j]>cal[i]){
                dp[i] = max(dp[j] + 1, dp[i]);
            }
        }
        maxn = max(dp[i], maxn);
    }
    int maxf = 0;
    fan[0] = 1;
    for (int i = 0; i < n;i++){
       // int flag = 1;
        if(dp[i]==1)
            fan[i] = 1;
        for (int j = 0; j <i;j++){
            if(cal[i]==cal[j]&&dp[i]==dp[j]){
                //dp[j] = 0;
                fan[j] = 0;
                //flag = 0;
            }
            else if(dp[i]==dp[j]+1&&cal[j]>cal[i]){
                fan[i] += fan[j];
            }     

        }

    }
    for (int i = 0; i < n;i++){
        if(dp[i]==maxn){
            maxf+= fan[i];
        }
    }
        fcout << maxn << maxf;

    fcin.close();
    fcout.close();

        return 0;
}