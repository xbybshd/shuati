/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 100009

const int INF = 0x7fffffff;

#define Mod 1000000007

int n, m, k, t;
#define Mod 1000000007
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);


struct left_heap {
    struct node {
        int lc, rc, dist, val, id;//dist就是左偏树特别的定义，到最近根节点的距离，id是防止重复数据的唯一索引
    };
    node tree[MAX];
    int rt[MAX];
    void init() {
        tree[0].dist = -1;//重要：所有的空节点都是第0个节点，距离设为-1；
    }
    int merge(int a, int b) {//以a为根节点，将b合并进a中
        if (!a || !b) {
            return a + b;
        }
        if (tree[a].val > tree[b].val || (tree[a].val == tree[b].val && tree[a].id > tree[b].id)) swap(a, b);
        //小根堆，如果a的节点大于b的，就要让b先进来，所以要将ab交换
        tree[a].rc = merge(tree[a].rc, b);//将a的右子树节点与b合并
        if (tree[tree[a].lc].dist < tree[tree[a].rc].dist)
            swap(tree[a].lc, tree[a].rc);//右子树距离应该比左子树小，在一个节点为空的时候，空节点距离为-1，刚好
        tree[a].dist = tree[tree[a].rc].dist + 1;//更新a的距离
        return a;
    }

    int find(int x) {
        return rt[x] == x ? x : rt[x] = find(rt[x]);//并查集路径压缩
    }
};

left_heap th;



int main()
{
    fcin >> n >> m;
    th.init();
    for (int i = 1;i <= n;i++) {
        int a;
        fcin >> a;
        th.tree[i].val = a;
        th.rt[i] = i;
        th.tree[i].id = i;
    }
    int mi = 2;
    while (m--) {
        int op;
        fcin >> op;
        fcout << mi << " ";
        mi++;
        if (op == 1) {
            int x, y;
            fcin >> x >> y;
            if (th.tree[x].val == -1 || th.tree[y].val == -1) {
                continue;
            };
            x = th.find(x);
            y = th.find(y);
            if (x != y)
                th.rt[x] = th.rt[y] = th.merge(x, y);
        }
        else {
            int x;
            fcin >> x;//删除就是把首节点的左右子树合并
            if (th.tree[x].val == -1)
                fcout << -1;
            else {
                x = th.find(x);
                fcout << th.tree[x].val;
                th.tree[x].val = -1;
                th.rt[th.tree[x].lc] = th.rt[th.tree[x].rc] = th.rt[x] =
                    th.merge(th.tree[x].lc, th.tree[x].rc);//你是把根节点删除了，但是在并查集上，挂在根节点上的子节点\
                                                                               并不只是左右子节点，根节点之后还有用，所以要把根节点的\
                                                                               父亲也更新到新节点
                th.tree[x].lc = th.tree[x].rc = 0;
            }
        }
        fcout << endl;

    }

    fcin.close();
    fcout.close();

    return 0;
}