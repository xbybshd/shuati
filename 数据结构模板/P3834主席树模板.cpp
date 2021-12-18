/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 200010

const int INF = 0x7fffffff;

#define Mod 1000000007

int n, m, k, t;
#define Mod 1000000007

struct treenode {
    int l, r, val, size;
};

treenode tree[MAX * 20];
struct numnode {
    int num, id;
};

numnode a[MAX];
int ind2dis[MAX];
int dis2real[MAX];
int root[MAX];
int cnt = 0;
int na;
void dis() {
    sort(a + 1, a + n + 1, [](numnode x, numnode y) {if (x.num != y.num) return x.num < y.num;else return x.id < y.id; });
    na = 1;
    ind2dis[a[1].id] = 1;
    dis2real[1] = a[1].num;
    for (int i = 2; i <= n; i++) {
        if (a[i].num != a[i - 1].num)
            na++;
        ind2dis[a[i].id] = na;
        dis2real[na] = a[i].num;
    }
}
//i为输入顺序第几个数，ind2dis[i]为离散化之后的值,也就是第几大，但此时a已经安装大小排好序了，dis2real[b[i]].num为实际值

void build(int& k, int l, int r) {
    k = ++cnt;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(tree[k].l, l, mid);
    build(tree[k].r, mid + 1, r);
}

void update(int& now, int pre, int l, int r, int x) {
    now = ++cnt;
    tree[now] = tree[pre];
    tree[now].size++;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        update(tree[now].l, tree[pre].l, l, mid, x);
    else
        update(tree[now].r, tree[pre].r, mid + 1, r, x);
}

int query(int l_node, int r_node, int l, int r, int k) {
    int x = tree[tree[r_node].l].size - tree[tree[l_node].l].size;
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (k <= x)
        return query(tree[l_node].l, tree[r_node].l, l, mid, k);
    else
        return query(tree[l_node].r, tree[r_node].r, mid + 1, r, k - x);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].num;
        a[i].id = i;
    }
    dis();
    build(root[0], 1, na);
    for (int i = 1; i <= n; i++) {
        update(root[i], root[i - 1], 1, na, ind2dis[i]);
    }

    while (m--) {
        int nl, nr, nk;
        cin >> nl >> nr >> nk;
        int disnum = query(root[nl - 1], root[nr], 1, na, nk);
        int ans = dis2real[disnum];
        cout << ans << endl;
    }

    return 0;
}