/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

#include <iostream>
#include <string>
#include <utility>
#define MAX 1000
const int INF = 0x7fffffff;
int n, m;
class splay {
public:
    class node {
    public:
        int ch[2];
        int f;
        int sum = 0;
        int val = -INF; //起始值设为0的时候有负值会把逻辑上为空但真实值为0的节点也算上，所以可以统一设为负值
        int recv;
        int lazy;
        node() {};
        node(int _val)
            : val(_val) {
            recv = sum = 1;
        }
    };
    node tree[MAX];
    int cnt, points;
    int root = 0;
    vector<int> print_vec;

    void update(int x) {
        tree[x].sum = tree[tree[x].ch[0]].sum + tree[tree[x].ch[1]].sum + tree[x].recv;
    }

    int identify(int x) {
        return tree[tree[x].f].ch[0] == x ? 0 : 1;
    }

    void connect(int x, int father, int son) {
        tree[x].f = father;
        tree[father].ch[son] = x;
    }

    void rotate(int x) { //旋转一个节点
        int y = tree[x].f;
        int z = tree[y].f;
        int y_son = identify(x);
        int z_son = identify(y);
        int b = tree[x].ch[y_son ^ 1];
        connect(b, y, y_son);
        connect(y, x, y_son ^ 1);
        connect(x, z, z_son);
        update(y);
        update(x);
    }

    int newnode(int v, int f) { //这个是纯粹的在
        cnt++;
        tree[cnt].val = v;
        tree[cnt].f = f;
        tree[cnt].sum = tree[cnt].recv = 1;
        return cnt;
    }

    int build(int l, int r, int fa) {
        int mid = (l + r) >> 1; //标签从0开始建树，先建立的节点去中间
        int c_num = newnode(mid, fa);
        if (l == r) {
            return c_num; //左右相等，直接返回
        }
        if (l < mid)
            tree[c_num].ch[0] = build(l, mid - 1, c_num);
        if (r > mid)
            tree[c_num].ch[1] = build(mid + 1, r, c_num);
        update(c_num);
        return c_num;
    }

    void splay_ro(int x, int to) { //这种写法是将x旋转到to的子节点，即to之下，这种形式需要编号为0的节点作为超级节点
        while (tree[x].f != to) {
            int up_x = tree[x].f;
            if (tree[up_x].f == to) //当x父亲的父亲是to的时候，因为只要旋转一次
                rotate(x);
            else if (identify(x) == identify(up_x)) { //x与自己父节点共线，则先旋转父节点，再转x，这样存在两次共线的时候，深度会减1
                rotate(up_x); //spaly 双旋
                rotate(x);
            }
            else {
                rotate(x); //splay 单旋
                rotate(x);
            }
        }
        if (to == 0) { //旋转的目的节点父亲是超级节点，那么超级节点之下就是root
            root = x;
        }
    }

    int getroot() {
        return root;
    }
    void push_down(int x) {
        if (x && tree[x].lazy) {
            tree[tree[x].ch[0]].lazy ^= 1;
            tree[tree[x].ch[1]].lazy ^= 1;
            swap(tree[x].ch[0], tree[x].ch[1]);
            tree[x].lazy = 0;
        }
    }
    int find(int v) {
        v++; //权值，或者说顺序为0的节点，他自己的recv也是为1的，所以当v的顺序是从0开始的时候，在查权值之前要加1
        int now = root;
        while (1) {
            push_down(now); //查一个节点之前，首先要把它lazy标记翻下去
            if (v == tree[tree[now].ch[0]].sum + 1) //当前节点的中序，如果按照从1开始，就是左子树的总节点数+1，如果刚好相等说明找的就是这个节点
                return now;
            else if (v <= tree[tree[now].ch[0]].sum) { //节点顺序等于小于左子树的总结点数，就往左子树节点找
                now = tree[now].ch[0];
            }
            else {
                v -= (tree[tree[now].ch[0]].sum + 1); //除了上面的情况，就是落在右子树
                now = tree[now].ch[1];
            }
        }
    }
    void reserve(int l, int r) {
        int left = find(l - 1);
        int right = find(r + 1);
        splay_ro(left, 0);
        splay_ro(right, left); //右边的大于左边，那么右边绝对是在左边的右子树
        int cur = tree[right].ch[0];
        tree[cur].lazy ^= 1;
    }
    void print(int cur) {
        if (tree[cur].lazy == 1) {
            push_down(cur);
        }
        if (tree[cur].ch[0] != 0)
            print((tree[cur].ch[0]));
        print_vec.push_back(tree[cur].val);
        if (tree[cur].ch[1] != 0)
            print((tree[cur].ch[1]));
    }
};

splay st;

int main() {
    fcin >> n >> m;
    st.root = st.build(0, n + 1, 0);
    // st.print_vec.clear();
    // st.print(st.root);
    // cout << st.root << '\n';
    // for (int i = 0; i < n + 2; i++) {
    //     cout << st.print_vec[i];
    //     if (i != n + 1)
    //         cout << " ";
    // }
    // cout << "\n";
    while (m--) {
        int l, r;
        fcin >> l >> r;
        st.reserve(l, r);
        // st.print_vec.clear();
        // st.print(st.root);
        // cout << st.root << '\n';
        // for (int i = 0; i < n + 2; i++) {
        //     cout << st.print_vec[i];
        //     if (i != n + 1)
        //         cout << " ";
        // }
        // cout << "\n";
    }
    st.print_vec.clear();
    st.print(st.root);
    // fcout << st.root << '\n';
    for (int i = 1; i < n + 1; i++) {
        fcout << st.print_vec[i];
        if (i != n)
            fcout << " ";
    }

    fcin.close();
    fcout.close();

    return 0;
}