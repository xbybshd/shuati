/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include <bits/stdc++.h>
#include <map>
#include <queue>

// #include <iostream>
// #include <cstring>

using namespace std;
#define MAX 1600
#define INF 0x3f3f3f3f
#define MAXF 12000
#define P 19650827
// int n, m, r, c, s;
// int sx, sy;
// int cnt=0;
// int root = 1;
// int maxans = 0;
typedef unsigned long long ull;
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

int kmp[MAX] = { 0 }; //kmp数组第0，和1都是0；
int n, nj;
int l1, l2;

char s1[MAX];
char s2[MAX];

// kmp的理解，对于模式串，就是找当前0,j内，真前缀和真后缀相同的最大情况

int main() {
    nj = 0;
    fcin >> s1 + 1 >> s2 + 1; //从第一位开始输入字符串
    l1 = strlen(s1 + 1);
    l2 = strlen(s2 + 1);
    // 以下都是从下标1开始，自匹配到i的时候，试探匹配nj+1是否相同，这里暗示，i-1与nj是匹配的，如果i与nj+1不一样，此时最后一个匹配的
    // 是nj，和i-1.下一个与i-1匹配的就是kmp[nj]，nj回退到kmp[nj]
    for (int i = 2; i <= l2; i++) { //s2数组先自我匹配,从第二个开始，每次将j的下一个与当前i比较，判断是+1还是回退，所以j要从首字符之前开始\
    就是0；
        while (nj && s2[i] != s2[nj + 1]) { //j没有回退到第0个的话，并且s1[i]不等于j的下一个，回退
            nj = kmp[nj];
        }
        // 如果i与nj+1匹配，此时i-1也与nj匹配，此时nj可以++，而且也就是说，对于后面的过程来说，如果在后面模式串到了i的位置，i+1与匹配串
        // 不匹配，那么模式串会回到新的nj的位置，继续比较。
        if (s2[i] == s2[nj + 1]) { //如果s1[i]等于j的下一个，j加一，可以比较下一个了
            nj++;
        }
        kmp[i] = nj; //这个时候的i一定与j相等，
    }

    for (int i = 1; i <= l1; i++) {
        while (nj && s1[i] != s2[nj + 1]) {
            nj = kmp[nj];
        }
        if (s1[i] == s2[nj + 1]) {
            nj++;
        }
        if (nj == l2) { //匹配完之后，下一个就处理成必然错配的情况，回退到与最后一个字符相等的j
            fcout << i - l2 + 1 << endl;
            nj = kmp[nj];
        }
    }

    for (int i = 1; i <= l2; i++)
        fcout << kmp[i] << " ";

    fcin.close();
    fcout.close();

    return 0;
}