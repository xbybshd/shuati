#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
#define MAX 102
#define MAXN 0x3f3f3f3f
int g[MAX][MAX] = {0};
int dp[MAX][MAX] = {0};
//int num[MAX] = {0};
int n, m;
int max_ele(int a,int b,int c,int d){
    if (b>a)
        a = b;
    if (c>a)
        a = c;
    if (d>a)
        a = d;
    return a;
}

int main()
{


    cin >> n >> m;
    for (int i = 1; i <= n;i++){
        for (int j = 1; j <= m;j++){
            cin >> g[i][j];
        }
    }
    int maxdp = 0;
    for (int i =1; i <=n;i++){
        for (int j = 1; j <=m;j++){
            if(g[i][j]==0){
                continue;
            }
            if(dp[i-1][j-1]==0){
                dp[i][j] = 1;
            }

            else{
                int kk = dp[i - 1][j - 1];
                int vi = i - kk;
                int vj = j - kk;
                int xk, yk;
                xk = yk = 0;
                for (int ui = i - 1; ui >= vi;ui--){
                    if(g[ui][j]==1){
                        xk++;
                    }
                    else{
                        break;
                    }
                }
                for (int uj = j - 1; uj >= vj;uj--){
                    if(g[i][uj]==1){
                        yk++;
                    }
                    else{
                        break;
                    }
                }
                int maxe = xk < yk ? xk : yk;
                dp[i][j] = maxe + 1;
                maxdp = maxdp > dp[i][j] ? maxdp : dp[i][j];
            }
        }
    }
    int aa = maxdp;
    cout << aa;



        return 0;

}

