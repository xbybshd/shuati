/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-05-19 02:22:09
 */
#include <bits/stdc++.h>
#include <map>
#include <queue>
#include <string>

// #include <iostream>
// #include <cstring>

using namespace std;
#define MAX 10010
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
// #define Mod 1000000007
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

int n, m, t;

struct node
{
    int l, r, k;
    node()
    {
        l = r = k = 0;
    }
};

int fa[MAX << 1];
int da[MAX << 1];
int ds[MAX << 1];
node ques[MAX << 1];
int cnt = 0;
char pd[7];

void discrete()
{
    for (int i = 1; i <= m; i++)
    {
        int xl, xr;
        fcin >> xl >> xr >> pd;
        ques[i].k = (pd[0] == 'e' ? 0 : 1);
        ques[i].l = xl;
        ques[i].r = xr;
        da[++cnt] = xl; //离散化，先把所有可能的值都填在数组里面
        da[++cnt] = xr;
    }
    sort(da + 1, da + cnt + 1);                //然后所有可能的值排序
    n = unique(da + 1, da + cnt + 1) - da - 1; //最后去重，算出来一共有多少个值
}

int get(int x)
{
    if (x == fa[x])
        return x;
    int root = get(fa[x]); //得到当前节点的根
    ds[x] ^= ds[fa[x]];    //当前节点的权要加上父节点的权
    return fa[x] = root;   //返回父节点，此时父节点已经赋值给了根
}

int main()
{
    fcin >> n >> m;
    discrete();
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++)
    {
        int x = lower_bound(da + 1, da + n + 1, ques[i].l - 1) - da; //离散化是通过给定之前的值，在所有值的数组里面找对应的值，如果返回下标
        int y = lower_bound(da + 1, da + n + 1, ques[i].r) - da;
        int p = get(x); //找到集合根节点
        int q = get(y);
        if (p == q) //如果同一个集合
        {
            if ((ds[x] ^ ds[y]) != ques[i].k) //奇偶性相同情况是否与给定相同
            {
                fcout << i - 1 << endl;
                return 0;
            }
        }
        else
        {
            fa[p] = q;
            ds[p] = ds[x] ^ ds[y] ^ ques[i].k; //不是一个集合就合并，把其中一个节点作为另一个父节点，然后子节点权值为两个节点权值（现在已经把\
            要查的两个节点都连到他们本身的父节点上了
        }
    }
    fcout << m;

    fcin.close();
    fcout.close();

    return 0;
}
