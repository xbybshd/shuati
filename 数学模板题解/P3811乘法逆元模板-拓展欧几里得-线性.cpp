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
#define MAX 300
#define INF 0x3f3f3f3f
#define MAXF 400
#define P 19650827
// int n, m, r, c, s;
// int sx, sy;
// int cnt=0;
// int root = 1;
// int maxans = 0;
typedef long long ll;
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);
ll n, m;
ll ins[MAX] = {0,1};


ll exgcd(ll a,ll b,ll&x,ll&y){
    if(b==0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll z = x;
    x = y;
    y = z - y * (a / b);
    return d;
}




int main()
{
    fcin >> n >> m;
    for (int i = 1; i <= n;i++){
        ll x, y;
        ll q = exgcd(i, m, x, y);
        x = (x%m + m) % m;
        fcout << x << endl;
    }
    fcout << ins[1] << endl;
    for (int i = 2; i <= n;i++){
        ins[i] = m - m / i * (ins[m % i]) % m;
        fcout << ins[i] << endl;
    }

        fcin.close();
    fcout.close();

        return 0;
}