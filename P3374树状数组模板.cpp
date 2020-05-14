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

int bit[MAX] = {0};//为数组内部是原始数量
inline int lowbit(int x){//lowbit函数，去最右边的1以及1右边的所有0，
    return x & (-x);
}

void add(int x,int k){//第x个数加上k
    while(x<=n){//x最大为数组元素总数
        bit[x] += k;//第x为加上k
        x +=lowbit(x);//x加上自己的lowbit
    }
}

int sum(int x){//统计区间[1,x]所有数之和
    int res = 0;
    while(x){//到0为止
        res += bit[x];//和加上x位的值
        x -= lowbit(x);//x减去自己的lowbit
    }
    return res;
}

int main()
{
    fcin >> n >> m;
    int xa;
    for (int i = 1; i <= n;i++){
        fcin >> xa;
        add(i, xa);//初始化从下标1开始，正常添加元素，第i为值加xa
    }
    for (int i = 1; i <= m;i++){
        int op, x, y;
        fcin >> op >> x >> y;
        if(op==1){
            add(x, y);
        }
        else{
            fcout << sum(y) - sum(x - 1) << endl; //求区间[x,y]所有元素之和即求sum(y)-sum(x-1);
        }
    }

        fcin.close();
    fcout.close();

        return 0;
}