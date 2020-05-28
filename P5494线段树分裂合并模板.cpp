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
// #define Mod 1000000007
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

int n, m, t;

int cnt = 1;

struct st_node
{
    int l = 0;
    int r = 0;
    int sum = 0;
    st_node(){};
};

st_node st[MAX << 2];

void push_up(int p)
{
    st[p].sum = st[st[p].l].sum + st[st[p].r].sum;
}

void insert(int p, int l, int r, int val, int change)
{
    if (l == r)
    {
        st[p].sum += change;
        return;
    }
    int mid = (l + r) >> 1;
    if (val <= mid)
    {
        if (!st[p].l)
        {
            cnt++;
            st[p].l = cnt;
        }
        insert(st[p].l, l, mid, val, change);
    }
    else
    {
        if (!st[p].r)
        {
            cnt++;
            st[p].r = cnt;
        }
        insert(st[p].r, mid + 1, r, val, change);
    }
    push_up(p);
}

int merge(int x, int y, int l, int r)
{
    if (!x)
        return y;
    if (!y)
        return x;
    if (l == r)
    {
        st[x].sum += st[y].sum;
        return x;
    }
    int mid = (l + r) >> 1;
    st[x].l = merge(st[x].l, st[y].l, l, mid);
    st[x].r = merge(st[x].r, st[y].r, mid + 1, r);
    push_up(x);
    return x;
}

int split(int x, int y, int k)
{
    y = ++cnt;
    int val = st[st[x].l].sum;
    if (k > val)
    {
        st[y].r = split(st[x].r, st[y].r, k - val);
    }
    else if (k == val)
    {
        swap(st[x].r, st[y].r);
    }
    else
    {
        swap(st[x].r, st[y].r);
        st[y].l = split(st[x].l, st[y].l, k);
    }
    st[y].sum = st[x].sum - k;
    st[x].sum = k;
    return y;
}

int query(int p, int l, int r, int ql, int qr)
{
    if (qr < l || ql > r)
        return 0;
    if (ql <= l && qr >= r)
    {
        return st[p].sum;
    }
    int mid = (l + r) >> 1;
    return query(st[p].l, l, mid, ql, qr) + query(st[p].r, mid + 1, r, ql, qr);
}

int kth(int p, int l, int r, int k)
{
    if (l == r)
    {
        return l;
    }
    int mid = (l + r) >> 1;
    if (st[st[p].l].sum >= k)
    {
        return kth(st[p].l, l, mid, k);
    }
    else
    {
        return kth(st[p].r, mid + 1, r, k - st[st[p].l].sum);
    }
}

int num_set[MAX];
int nc = 1;

int main()
{
    fcin >> n >> m;
    num_set[1] = 1;
    for (int i = 1; i <= n; i++)
    {
        int ca;
        fcin >> ca;
        insert(num_set[1], 1, n, i, ca);
    }

    while (m--)
    {
        int op, p;
        fcin >> op >> p;
        if (op == 0)
        {
            int x, y;
            fcin >> x >> y;
            int k1 = query(num_set[p], 1, n, 1, y);
            int k2 = query(num_set[p], 1, n, x, y);
            int temp = 0;
            nc++;
            num_set[nc] = split(num_set[p], num_set[nc], k1 - k2);
            temp = split(num_set[nc], temp, k2);
            num_set[p] = merge(num_set[p], temp, 1, n);
        }
        else if (op == 1)
        {
            int t;
            fcin >> t;
            num_set[p] = merge(num_set[p], num_set[t], 1, n);
        }
        else if (op == 2)
        {
            int val, change;
            fcin >> change >> val;
            insert(num_set[p], 1, n, val, change);
        }
        else if (op == 3)
        {
            int x, y;
            fcin >> x >> y;
            int q = query(num_set[p], 1, n, x, y);
            fcout << q << endl;
        }
        else
        {
            int k;
            fcin >> k;
            if (st[num_set[p]].sum < k)
            {
                fcout << "-1" << endl;
            }
            else
            {
                int qk = kth(num_set[p], 1, n, k);
                fcout << qk << endl;
            }
        }
    }
    fcin.close();
    fcout.close();

    return 0;
}
