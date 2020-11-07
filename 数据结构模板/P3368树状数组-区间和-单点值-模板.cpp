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
int bit2[MAX] = {0};
int cal[MAX];
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

void add2(int x,int k){//第x个数加上k
    while(x<=n){//x最大为数组元素总数
        bit2[x] += k;//第x为加上k
        x +=lowbit(x);//x加上自己的lowbit
    }
}

int sum2(int x){//统计区间[1,x]所有数之和
    int res = 0;
    while(x){//到0为止
        res += bit2[x];//和加上x位的值
        x -= lowbit(x);//x减去自己的lowbit
    }
    return res;
}

int main()
{
    fcin >> n >> m;
    int xa;
    for (int i = 1; i <= n;i++){
        fcin >> cal[i];
        // add(i, xa);//初始化从下标1开始，正常添加元素，第i为值加xa
    }
    for (int i = 1; i <= m;i++){
        int op, x, y, k;
        fcin >> op;
        if(op==1){
            fcin >> x >> y >> k;//区间[x,y]全部加上k
            add(x, k);//所有包含x的都加上k
            add2(y, k);//所有包含y的都加上k
        }
        else{
            fcin >> x;
            fcout << sum(x) - sum2(x - 1) +cal[x]<< endl; //求某个点x的值，用左端点的树状数组sum(x)-右端点的树状数组sum1(x-1)\
            含义：左端点的意思是从l------一直往后算和的树状数组都加上了k\
                右端点的意思是从      r-------一直往后都加上了k，例如在l，r之间的一点，新数组的和是小于原来数组的
                
        }
    }

        fcin.close();
    fcout.close();

        return 0;
}