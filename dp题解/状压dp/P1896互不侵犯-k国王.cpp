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

// https://www.luogu.com.cn/blog/xcg--123/ti-xie-p1896-scoi2005-hu-fou-qin-fan

using inll = unsigned long long;
#define Mod 1000000000
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);
long long n, k, f[10][100][1024], state[1024], cnt[1024];
/*
    f[10][100][1024],10是行数，100是国王数量，1024是状态数
    state[1024]是状态总数
    cnt[1024] 是每个状态1的数量，因为需要统计每个状态具有的国王数
*/
int main() {
    fcin >> n >> k;
    f[0][0][0] = 1; //按照这种写法开始的 0维设为1
    int max_state = 1 << n;
    int num = 0;
    for (int i = 0; i < max_state; i++) {
        int tot = 0;
        int s = i;
        while (s) {
            tot += (s & 1);
            s >>= 1;
        }
        cnt[i] = tot;
        if ((((i << 1) | (i >> 1)) & i) == 0) { //左右不相交的简便写法
            state[++num] = i;
        }
    }

    for (int i = 1; i <= n; i++) { //第一层行数
        for (int u = 1; u <= num; u++) { //第二层是当前层状态
            int s1 = state[u];
            for (int v = 1; v <= num; v++) { //第三层是上一层状态
                int s2 = state[v];
                if (((s2 | (s2 << 1) | (s2 >> 1)) & s1) == 0) { //当前层与上一层左右不相交，正常不相交的简便写法
                    for (int j = 0; j <= k; j++) { //类似于背包问题，遍历国王数
                        if (j - cnt[s1] >= 0) {
                            f[i][j][s1] += f[i - 1][j - cnt[s1]][s2]; /*状态的三层，当前层数下，国王数确定的状态，
                                                                    会从上一层，国王数减去当前层数国王数的相容状态转移过来*/
                        }
                    }
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= num; i++) {
        ans += f[n][k][state[i]];
    }
    fcout << ans;

    fcin.close();
    fcout.close();

    return 0;
}