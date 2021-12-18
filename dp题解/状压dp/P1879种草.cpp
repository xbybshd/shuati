/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 210

#define INF 0x5000000

using inll = unsigned long long;
#define Mod 1000000000
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);
int n, m, f[13][4096], fid[13][13], same[13], state[4096];
/* f 行数 ，列数的所有状态总和，存在位运算 2^列数
   fid  原始行列点矩阵
   same  原始行列矩阵中每一行转换为位运算，得到的值
   state 第一遍自筛时，每一行可能的状态总数组，为1代表在自筛的时候，当前状态可行
*/

int main() {
    fcin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            fcin >> fid[i][j];
            same[i] = (same[i] << 1) + fid[i][j];
        }
    }
    int max_state = 1 << m;
    f[0][0] = 1;
    // 自筛，当前状态左右不可相邻
    for (int i = 0; i < max_state; i++) {
        state[i] = ((i & (i << 1)) == 0) && ((i & (i >> 1)) == 0);
    }
    for (int i = 1; i <= n; i++) {
        int now_state = same[i];
        for (int j = 0; j < max_state; j++) {
            if (state[j] == 1 && ((j & now_state) == j)) {
                for (int k = 0; k < max_state; k++) {
                    if ((j & k) == 0) {
                        f[i][j] = (f[i][j] + f[i - 1][k]) % Mod;
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < max_state; i++) {
        ans += f[n][i];
        ans %= Mod;
    }
    fcout << ans;

    fcin.close();
    fcout.close();

    return 0;
}