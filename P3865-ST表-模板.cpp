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
#define M 100
int n, m, r, c, s;
int sx, sy;
int cnt=0;
int root = 1;
int maxans = 0;
//typedef long long ll;
#define Mod 1000000007
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

int st[MAX][21] = {0};
int cal[MAX] = {0};

int query(int l,int r){
    int k = log(r - l + 1)/log(2);//k取区间长度的2对数
    return max(st[l][k], st[r - (1 << k) + 1][k]);//l------------l+2^(k)
}                                                 //     r-(2^k)+1--------------r  区间长度都是k次方，因为包含左右区间所以+1


int main()
{
    fcin >> n >> m;
    for (int i = 1; i <= n;i++){
        fcin >> st[i][0];
    }

    int up = log(n) / log(2) + 1; //st表的一个特征是区间左右都会包含，所以区间长度就是r-l+1;
    for (int j = 1; j <=up;j++){//up超过区间长度也无所谓，底层循环的i会越界直接不执行for
        for (int i = 1; i <= (n - (1 << j) + 1);i++){//从n开始往回，数2^j个，最后停下来的要包含左区间的数和右区间n，所以是\
        n-2^j+1,而且i是等于，要取到边界
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);//i---i+2^(j-1)  i+2^(j-1)-----i+2^(j-1)+2^(j-1)
        }
    }
    int l, r;
    for (int i = 1; i <= m;i++){
        fcin >> l >> r;
        fcout << query(l, r) << endl;
    }

        fcin.close();
    fcout.close();

        return 0;
}