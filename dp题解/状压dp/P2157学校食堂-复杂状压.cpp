/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2021-12-25 01:36:36
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 210

#define INF 0x5000000

using inll = unsigned long long;
#define Mod 1000000000
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

const int max_num = 0x3f3f3f3f;
int t, n, bi[1005], ti[1005], dp[1005][256][17];
/*

    bi 忍耐度，数量为同学的数量
    ti 做菜时间，数量为同学数量
    dp 同学数量-后面7个同学打饭状态-前8个后8个同学

    dp[i][j][k],当从1到第i-1个同学，都已经打完饭时，包括第i个人以及从i+1开始后面7个人打饭情况(状压)，最后一个打饭的同学是i+k
    在实际情况中
    -8 -7 -6 -5 -4 -3 -2 -1(i-1) 0(i) 1 2 3 4 5 6 7   一共16个同学，k要做偏移，[-8,7],k+8代表当前i(0),
    第三维度的意思是  最后一个打饭的同学，是第 i + k(第三维度)个同学。实际情况下，如果最后一个打饭的是第i位，应该是i+k+8;
    https://www.luogu.com.cn/blog/user30817/solution-p2157
*/

int main() {
    fcin >> t;
    int max_state = 1 << 8;
    while (t--) {
        fcin >> n;
        memset(bi, 0, sizeof(bi));
        memset(ti, 0, sizeof(ti));
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            fcin >> ti[i] >> bi[i];
        }
        dp[1][0][7] = 0; //初始化
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < max_state; j++) {
                for (int k = -8; k <= 7; k++) {
                    if (dp[i][j][k + 8] != 0x3f3f3f3f) {
                        if (j & 1) { // 如果第i位同学打完了饭，那就说明最后一个打饭的是第i位，所以i可以向后移动而最后结果不变\
                        是一个等价关系。
                            dp[i + 1][j >> 1][k + 7] = min(dp[i + 1][j >> 1][k + 7], dp[i][j][k + 8]);
                        }
                        else {
                            int limit = 0x3f3f3f3f;
                            for (int l = 0; l <= 7; l++) { //如果i位同学没有打完饭，那么考虑先打后面7位同学，将后面7位同学没有打饭的同学\
                            情况进行枚举(已经打过的就跳过)
                                if (!((j >> l) & 1)) {
                                    if (i + l > limit) { //从前到后枚举，每次枚举的时候都要拿当前同学的最大忍耐范围更新英雄总忍耐范围 limit
                                        break;
                                    }
                                    limit = min(limit, i + l + bi[i + l]);
                                    dp[i][j | (1 << l)][l + 8] = min(dp[i][j | (1 << l)][l + 8], dp[i][j][k + 8] + (i + k ? ti[i + k] ^ ti[i + l] : 0));
                                }
                            }
                        }
                    }
                }
            }
        }
        int ans = 0x7fffffff;
        for (int k = 0; k <= 8; k++) {
            ans = min(ans, dp[n + 1][0][k]);
        }
        fcout << ans << endl;
    }

    fcin.close();
    fcout.close();

    return 0;
}