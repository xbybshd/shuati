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
#define MAX 5009
#define INF 0x3f3f3f3f
#define MAXF 12000
#define P 19650827
int n, m, r, c, s;
int sx, sy;
int cnt=0;
int root = 1;
int maxans = 0;
typedef unsigned long long ull;
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

int cal[MAX] = {0};

int qsort(int l,int r){
    if(l==r&&l==m)
        return cal[l];
    int mid = (l + r) / 2;//求中点
    int temp = cal[mid];//缓存中点值
    cal[mid] = cal[l];//让中点值等于开始值
    int i = l;
    int j = r;
    while(i<j){
        while(i<j&&cal[j]>=temp)
            j--;
        cal[i] = cal[j];
        while(i<j&&cal[i]<=temp)
            i++;
        cal[j] = cal[i];
    }
    cal[i] = temp;//缓存值等于最后的i值
    if(i==m)
        return temp;
    else if(i<m){
        return qsort(i + 1, r);
    }
    else{
        return qsort(l, i - 1);
    }
    
    
}

int ff[MAX*4] = {0};
int main()
{
    fcin >> n >> m;
    for (int i = 1; i <= n;i++){
        int x;
        fcin >>x;
        if(!ff[x]){
            cal[++cnt]=x;//用数组去重，如果数据范围变大，可以用map 
            ff[x]=true;
        }
    }
    int ans = qsort(1, cnt);
    fcout << ans;

    fcin.close();
    fcout.close();

        return 0;
}