/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include<bits/stdc++.h>
#include <queue>
#include <map>
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
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);
int n, m;
ull mod = 212370440130137957ll;//大素数
int base = 131;//进制基数
char ss[MAX];
ull hs[MAXF];

ull hash_s(char s[]){
    int sl = strlen(s);
    ull ans = 0;
    for (int i = 0; i < sl;i++){
        ans = (ans * base + (ull)s[i]) % mod;//加完进制基数之后对大质数取模
    }
    return ans;
}

int main()
{
    fcin >> n;
    for (int i = 1; i <= n;i++){
        fcin >> ss;
        hs[i] = hash_s(ss);
    }
    sort(hs + 1, hs + n + 1);//排序
    int res = 0;
    for (int i = 1; i <= n;i++){
        if(hs[i]!=hs[i+1])
            res++;
    }
    fcout << res;

    fcin.close();
    fcout.close();

        return 0;
}