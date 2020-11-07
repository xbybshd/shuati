/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-09-19 20:36:10
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 104
int n, m, t;

//typedef long long ll;
#define Mod 1000000007
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);
int cal[MAX];
int dp[2][MAX];

int main()
{
    //二维dp，dp[i][j]=sum(dp[i][j-k])(k从0到ai);所以可以用滚动数组优化

    fcin >> n >> m;
    for (int i = 0;i < n;i++) {
        fcin >> cal[i];
    }
    dp[1][0] = 1;//滚动数组优化注意点1；如果从0开始，那么1数组的首项要初始化，一般可以把第一项设为0，不然可能整个结果为0；
    for (int i = 0;i < n;i++) {
        int ni = i % 2;
        int pni = 1 - ni;
        int cali = cal[i];
        for (int j = 0;j <= m;j++) {//j可以从0开始，因为下面对于k的值有限制不超过j
            dp[ni][j] = 0;
            for (int k = 0;k <= min(j, cali);k++) {
                dp[ni][j] = (dp[ni][j] + dp[pni][j - k]) % Mod;//当前滚动数组值加上前一个值
            }
        }
    }
    fcout << dp[(n - 1) % 2][m];




    fcin.close();
    fcout.close();

    return 0;
}