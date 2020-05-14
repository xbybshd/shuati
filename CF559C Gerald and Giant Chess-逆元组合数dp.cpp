/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include<bits/stdc++.h>
#include <queue>
#include <map>
#include <string>
// #include <iostream>
// #include <cstring>

using namespace std;
#define MAX 5009
#define INF 0x3f3f3f3f
#define MAXF 2003
#define P 19650827
int n, m, r, c, s;
int sx, sy;
int cnt=0;
int root = 1;
int maxans = 0;
//typedef long long ll;
#define Mod 1000000007
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

int fac[MAX * 2 + 10];
int inv[MAX * 2 + 10];
int ans[MAXF] = {0};

struct node{
    int x, y;
    node(){};
    node(int xx, int yy) : x(xx), y(yy){};
    bool operator <(const node& b){
        if(x!=b.x){
            return x < b.x;
        }
        else{
            return y < b.y;
        }
    }
};
node cal[2010];

int q_pow(int x,int p){//快速幂
    int ans = 1;
    while(p){
        if(p&1)
            ans = (1ll * ans * x) % Mod;
        x = (1ll * x * x) % Mod;
        p>>=1;
    }
    return ans;
}

void pre_porcss(){//预处理n!的阶乘和inv(n!)
    int maxm =2* max(n, m);
    fac[0] = 1;
    for (int i = 1; i <= maxm;i++){//处理阶乘
        fac[i] = (1ll * fac[i - 1] * i) % Mod;//可用1ll相乘强制longlong
    }
    inv[maxm] = q_pow(fac[maxm], Mod - 2);
    for (int i = maxm - 1; i >= 0;i--){
        inv[i] = 1ll * inv[i + 1] * (i + 1) % Mod; //inv((n-1)!)=inv(n!)*n%mod;
    }
}

int Combination(int nn,int mm){//组合数逆元求法
    if(nn<mm)
        return 0;
    int cc = (1ll * fac[nn] * inv[nn - mm] % Mod * inv[mm] % Mod); //C(n,m)=n!*inv((n-m)!)%mod*inv(m!)%mod;
    return cc;
}



int ff[MAX*4] = {0};
int main()
{
    fcin >> n >> m >> c;
    for (int i = 0; i < c;i++){
        int ux, uy;
        fcin >> ux >> uy;
        cal[i] = node(ux, uy);
    }
    cal[c] = node(n, m);
    sort(cal, cal + c + 1);
    pre_porcss();
    for (int i = 0; i <= c;i++)
    { //棋盘从左上到右下路径C(n,n+m)
        ans[i] = Combination(cal[i].x + cal[i].y - 2,cal[i].x - 1);//代表走到第i个黑色点并且不经过之前所有黑色点的路径数量
        for (int j = 0; j < i;j++){
            ans[i] =((1ll*ans[i] -(1ll * ans[j] * Combination( cal[i].x - cal[j].x + cal[i].y - cal[j].y,cal[i].x - cal[j].x)%Mod)%Mod+Mod))%Mod;
        }//从直接到达当前黑色点的方案数减去之前每一个黑色点的方案数乘上从黑色点到当前黑色点的数量
    }
    fcout << ans[c];

    fcin.close();
    fcout.close();

        return 0;
}