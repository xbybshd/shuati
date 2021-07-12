/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 100

const int INF = 0x7fffffff;

#define Mod 1000000007

int n, m, k, t;
#define Mod 1000000007
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

int cal[MAX];//每一点实际值
int val[MAX];//此点对应哪一段
int tag[MAX];//此段的总标记
int ans[MAX];//此段的总和

void change(int l, int r) {
    int a = val[l];
    int b = val[r];
    if (a == b) {//在同一段内，段内修改
        for (int i = l;i <= r;i++) {
            ans[a] -= (cal[i] ^ tag[a]);//先得到当前的值，如果是1就减掉，因为当前值并不直接反应在cal上，存在整段修改tag，没有修改cal的情况
            cal[i] ^= 1;//修改当前值
            ans[a] += (cal[i] ^ tag[a]);//加上当前值
        }
    }
    else {
        for (int i = a + 1;i < b;i++) {
            tag[i] ^= 1;//整段修改tag
            ans[i] = t - ans[i];//只有01两种状态，那么和也就是相反而已
        }
        for (int i = l;i <= t * (a + 1);i++) {
            ans[a] -= (cal[i] ^ tag[a]);//头尾进行修改
            cal[i] ^= 1;
            ans[a] += (cal[i] ^ tag[a]);
        }
        for (int i = r;i > t * b;i--) {
            ans[b] -= (cal[i] ^ tag[b]);
            cal[i] ^= 1;
            ans[b] += (cal[i] ^ tag[b]);
        }
    }
}

int query(int l, int r) {
    int a = val[l];
    int b = val[r];
    int sum = 0;
    if (a == b) {
        for (int i = l;i <= r;i++) {
            sum += (cal[i] ^ tag[a]);//段内，每点查询即可
        }
    }
    else {
        for (int i = a + 1;i < b;i++) {
            sum += ans[i];//整段的时候，ans是在change的时候就更新了
        }
        for (int i = l;i <= t * (a + 1);i++) {
            sum += (cal[i] ^ tag[a]);//头尾也要分别考虑
        }
        for (int i = r;i > t * b;i--) {
            sum += (cal[i] ^ tag[b]);
        }
    }
    return sum;
}

int main()
{
    fcin >> n >> m;
    t = sqrt(n);
    for (int i = 1;i <= n;i++) {
        val[i] = (i - 1) / t;//段数从0开始
    }

    while (m--) {
        int op, x, y;
        fcin >> op >> x >> y;
        if (op == 0) {
            change(x, y);
        }
        else {
            int sum = query(x, y);
            fcout << sum << endl;
        }
    }



    fcin.close();
    fcout.close();

    return 0;
}