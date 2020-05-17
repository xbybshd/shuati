/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-05-17 23:55:25
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
#define Mod 1000000007
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

int n, m, t;
int cal[MAX];

struct st_node //线段树节点结构体,全为闭区间
{
    int l, r; //左右节点
    int sum;  //需要计算的，附和结合律的量，这里是区间和
    int tag;  //延迟标记
    st_node(){};
};

st_node st[MAX << 2]; //节点数大小乘以4

inline void push_up(int p) //从当前节点的两个子节点的值维护当前节点的值
{
    st[p].sum = st[p << 1].sum + st[p << 1 | 1].sum;
    int a = 1;
}

void build(int p, int l, int r) //建树,p为线段树节点序号，从1开始，l,r为左右区间
{
    st[p].l = l; //填入当前节点的左右区间
    st[p].r = r;
    if (l == r)
    {
        st[p].sum = cal[l]; //如果左右一样，直接填入值为输入值
        return;
    }
    int mid = (l + r) >> 1;        //取mid
    build(p << 1, l, mid);         //递归建树，[l,mid]
    build(p << 1 | 1, mid + 1, r); //[mid+1,r]
    push_up(p);                    //类似后序遍历，当前节点的值需要等两个子节点都建立完毕才可以填入
}

inline void modify(int p, int l, int r, int mod_t) //当前节点需要修改值和tag，用于延迟标记的下一层，需要下传标记
{
    st[p].tag += mod_t; //tag加上上一次传下来的
    st[p].sum += mod_t * (r - l + 1);
}

inline void push_down(int p, int l, int r) //当前节点为p，需要将延迟标记下传，把p的子节点都修改
{
    if (st[p].tag) //如果p的tag为0，说明不需要更新，或者已经更新过了,就结束
    {
        int mid = (l + r) >> 1;
        int mod = st[p].tag;         //需要更新的值
        modify(p << 1, l, mid, mod); //对两个子节点更新值和tag
        modify(p << 1 | 1, mid + 1, r, mod);
        st[p].tag = 0; //当前的tag清空
    }
}

void update(int p, int l, int r, int ul, int ur, int u) //区间更新，[ul,ur]区间内所有点加上u
{
    if (ul <= l && ur >= r) //如果查询区间完全包含当前区间，直接将当前区间值和tag更新即可，即延迟标记，下面的不需要遍历
    {
        st[p].sum += u * (r - l + 1);
        st[p].tag += u;
        return;
    }
    push_down(p, l, r); //如果跨区间，或者查询区间小于当前区间，就将延迟标记下传
    int mid = (l + r) >> 1;
    if (ul <= mid)
    {
        update(p << 1, l, mid, ul, ur, u); //视跨区间的情况，更新两个子节点区间，因为子区间已经标记下传，可以更新
    }
    if (ur > mid)
    {
        update(p << 1 | 1, mid + 1, r, ul, ur, u);
    }
    push_up(p); //等子节点区间更新之后，返回更新父节点
}

int query(int p, int l, int r, int ql, int qr) //查询区间为[ql,qr]，的区间和
{
    int res = 0;
    if (ql <= l && qr >= r) //如果查询区间完全包含当前区间直接返回
    {
        return st[p].sum;
    }
    int mid = (l + r) >> 1;
    push_down(p, l, r); //跨区间，延迟标记下传
    if (ql <= mid)
    {
        res += query(p << 1, l, mid, ql, qr);
    }
    if (qr > mid)
    {
        res += query(p << 1 | 1, mid + 1, r, ql, qr);
    }
    return res; //因为不涉及更新，所以父节点更新不需要
}

int main()
{
    fcin >> n >> m;
    st_node *k = new st_node();
    for (int i = 1; i <= n; i++)
    {
        fcin >> cal[i];
    }
    build(1, 1, n); //区间[1,n]建树
    while (m--)
    {
        int x;
        fcin >> x;
        if (x == 1)
        {
            int ul, ur, uk;
            fcin >> ul >> ur >> uk;
            update(1, 1, n, ul, ur, uk);
        }
        else
        {
            int ul, ur;
            fcin >> ul >> ur;
            int res = query(1, 1, n, ul, ur);
            fcout << res << endl;
        }
    }

    fcin.close();
    fcout.close();

    return 0;
}
