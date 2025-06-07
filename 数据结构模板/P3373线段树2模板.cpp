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
int cal[MAX];
int Mod = 0;

struct st_node {
    int l, r;
    int sum = 0;
    int tag = 0;
    int mul = 1;
    st_node() {};
};

st_node st[MAX << 2];

inline void push_up(int p) {
    st[p].sum = (st[p << 1].sum + st[p << 1 | 1].sum) % Mod;
    int a = 1;
}

void build(int p, int l, int r) {
    st[p].l = l;
    st[p].r = r;
    if (l == r) {
        st[p].sum = cal[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

// inline void modify_add(int p, int l, int r, int mod_t)
// {
//     st[p].tag += mod_t;
//     st[p].sum += mod_t * (r - l + 1);
// }

// inline void modify_mul(int p, int l, int r, int mod_t)
// {
//     st[p].mul *= mod_t;
//     st[p].sum += mod_t * (r - l + 1);
// }

inline void push_down(int p, int l, int r) //本质是修改子节点的结构体值，比如和，加法标记，乘法标记
{
    // if (st[p].tag)
    {
        int mid = (l + r) >> 1;
        int ls = p << 1;
        int rs = p << 1 | 1;
        st[ls].sum = (st[ls].sum * st[p].mul + (mid - l + 1) * st[p].tag) % Mod; //求和时，乘本体，加上区间乘上加法，区间的乘法在更新乘法的\
        的时候已经合并入加法
        st[rs].sum = (st[rs].sum * st[p].mul + (r - mid) * st[p].tag) % Mod;

        st[ls].mul = (st[ls].mul * st[p].mul) % Mod;
        st[rs].mul = (st[rs].mul * st[p].mul) % Mod;

        st[ls].tag = (st[ls].tag * st[p].mul + st[p].tag) % Mod; //有乘法的更新的时候，先将当前的加法标记乘上乘法在加更新的加法
        st[rs].tag = (st[rs].tag * st[p].mul + st[p].tag) % Mod;
        st[p].tag = 0;
        st[p].mul = 1;
    }
}

void update_add(int p, int l, int r, int ul, int ur, int u) {
    if (ul <= l && ur >= r) {
        st[p].sum = (st[p].sum + u * (r - l + 1)) % Mod;
        st[p].tag = (st[p].tag + u) % Mod;
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (ul <= mid) {
        update_add(p << 1, l, mid, ul, ur, u);
    }
    if (ur > mid) {
        update_add(p << 1 | 1, mid + 1, r, ul, ur, u);
    }
    push_up(p);
}

void update_mul(int p, int l, int r, int ul, int ur, int u) {
    if (ul <= l && ur >= r) {
        st[p].sum = (st[p].sum * u) % Mod;
        st[p].tag = (st[p].tag * u) % Mod; //更新乘法的时候也要更新加法标记
        st[p].mul = (st[p].mul * u) % Mod;
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (ul <= mid) {
        update_mul(p << 1, l, mid, ul, ur, u);
    }
    if (ur > mid) {
        update_mul(p << 1 | 1, mid + 1, r, ul, ur, u);
    }
    push_up(p);
}

int query(int p, int l, int r, int ql, int qr) {
    int res = 0;
    if (ql <= l && qr >= r) {
        return st[p].sum;
    }
    int mid = (l + r) >> 1;
    push_down(p, l, r);
    if (ql <= mid) {
        res = (res + query(p << 1, l, mid, ql, qr)) % Mod;
    }
    if (qr > mid) {
        res = (res + query(p << 1 | 1, mid + 1, r, ql, qr)) % Mod;
    }
    return res;
}

int main() {
    fcin >> n >> m >> Mod;
    //  st_node *k = new st_node();
    for (int i = 1; i <= n; i++) {
        fcin >> cal[i];
    }
    build(1, 1, n);
    while (m--) {
        int x;
        fcin >> x;
        if (x == 1) {
            int ul, ur, uk;
            fcin >> ul >> ur >> uk;
            update_mul(1, 1, n, ul, ur, uk);
        }
        else if (x == 2) {
            int ul, ur, uk;
            fcin >> ul >> ur >> uk;
            update_add(1, 1, n, ul, ur, uk);
        }
        else {
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
