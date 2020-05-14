#include <fstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <map>
#include <queue>
#include <deque>
#include <cstdlib>
#include <cassert>
#include <stack>
#include <list>
#include <ctime>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <utility>
#include <iterator>
#include <deque>
#include <cmath>

using namespace std;



#define MAX 500002
int n;
int cc[MAX] = {0};//原始序列
int ss[MAX] = {0};//排序的时候的目的数组，最后还要拷回去
typedef long long ll;
ll ans = 0;
void me(int ls,int le,int rs,int re){
    int t = 0;
    int lt, rt;
    lt = ls;
    rt = rs;
    int nt = le - ls + 1;//左半部分的长度，逆序是按照左半部分算的
    while(lt<=le&&rt<=re){
        if(cc[lt]<=cc[rt]){
            ss[t] = cc[lt];
            lt++;
            t++;
            nt--;//左半部分的数小于右半部分，发生逆序的时候，这个数在左半部分就不算了
        }
        else {
            ss[t] = cc[rt];
            rt++;
            t++;
            ans += nt;//否则加上残余的左半部分长度，默认两边都是已经排序好的
        }
    }
    while(lt<=le){
        ss[t] = cc[lt];
        t++;
        lt++;
    }
    while(rt<=re){
        ss[t] = cc[rt];
        t++;
        rt++;
    }
    memcpy(cc + ls, ss, (re - ls + 1) * sizeof(int));//拷贝会cc；
}
void merge(int l,int h){
    if(h==l){
        return;
    }//左右相等就返回，闭区间
   
    int m = l+(h - l) / 2;//求中点
    merge(l, m);//排序[l,m]
    merge(m+ 1, h);//排序[m+1,h]
    me(l, m, m + 1, h);//归并[l,m,m+1,h]
    return;
    
}

int main()
{

    scanf("%d",&n);
    for (int i = 0; i < n;i++){
        scanf("%d",&cc[i]);
    }
    merge(0, n - 1);
    printf("%lld",ans);


    return 0;

}

