/*
 * @Author: xbybshd 
 * @Date: 2020-07-19 21:55:37 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-07-19 22:02:20
 */

#include <bits/stdc++.h>
#include <map>
#include <queue>
#include <string>

// #include <iostream>
// #include <cstring>

using namespace std;
#define MAX 1000
#define INF 0x3f3f3f3f
#define MIN 0x80000000
#define MAXF 2003
#define P 19650827
#define M 100
// int n, m, r, c, s;
// int sx, sy;
// int cnt=0;
// int root = 1;
// int maxans = 0;
// typedef long long ll;
#define Mod 10000
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

int n, m, t;
int fp[MAX] = {0};
int gp[MAX] = {0};

int main()
{
    fcin >> n;

    fp[0] = 1;//f是完整地排列n列的方法，g是n列完整排列，而且n+1列多了半个的情况
    fp[1] = 1;
    gp[0] = 0;
    gp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        gp[i] = (gp[i - 1] + fp[i - 1]) % Mod;
        fp[i] = ((fp[i - 1] + fp[i - 2]) % Mod + (2 * gp[i - 2]) % Mod) % Mod;
    }

    fcout << fp[n];
    fcin.close();
    fcout.close();

    return 0;
}
