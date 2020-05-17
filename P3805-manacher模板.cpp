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
#define MAX 500
#define INF 0x3f3f3f3f
#define MAXF 2003
#define P 19650827
#define M 100
int n, m, r, c;
int sx, sy;
//int cnt=0;
int root = 1;
int maxans = 0;
//typedef long long ll;
#define Mod 1000000007
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

char s[MAX];
char s1[2 * MAX + 10];
int len = 1;
int p[2 * MAX + 10] = {0};

void change(){
    s1[0] = '$';
    s1[1] = '#';
    int l = strlen(s);

    for (int i = 0; i < l;i++){
        s1[++len] = s[i];//预处理$#a#b#c...
        s1[++len] = '#';
    }
}

int manacher(){//每一时刻都存在一个对称轴mid和这个对称轴的点最右边可以延伸的maxr，
    int mid = 0;
    int maxr = 0;
    int ans = 1;
    for (int i = 1; i <= len;i++){//从预处理之后的第1个开始循环
        if(i<=maxr)//当我们已经求出i对称轴左边的j的p[j]时，我们可以利用对称性\
直接得到当前i的基准p[i],基准p[i]是p[j]和i到对称轴最右maxr的最小值
            p[i] = min(p[(mid<<1)- i], maxr - i);
        while(s1[i+p[i]+1]==s1[i-p[i]-1])//然后从i的基准p[i]开始左右拓展
            ++p[i];
        if(i+p[i]>maxr){//如果拓展的右边大于当前maxr
            maxr = i + p[i];//替换maxr和对称轴
            mid = i;
        }
        if(p[i]>ans){
            ans = p[i]; //最大回文长度，为处理过后的最大回文半径p[i]; 
        }
    }
    return ans;
}

int main()
{
    fcin >> s;
    change();
    int res = manacher();
    fcout << res;

    fcin.close();
    fcout.close();

        return 0;
}