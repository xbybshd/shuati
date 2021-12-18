/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 210

#define INF 0x5000000

#define Mod 1000000007

using inll = unsigned long long;
inll n, m, k;
#define Mod 1000000007
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

class splay {
public:
    class node {
    public:
        int ch[2];
        int f;
        int sum = 0; // 此节点的所有节点数
        int val = 0; //起始值设为0的时候有负值会把逻辑上为空但真实值为0的节点也算上，所以可以统一设为负值
        int rand;
        bool lazy;
        char ca;
        node() {};
    };
    node tree[MAX];
    int cnt;
    int root = 0;
    int new_node(int v) {
        int now = ++cnt;
        tree[now].val = v;
        tree[now].rand = rand();
        tree[now].sum = 1;
        tree[now].lazy = false;
        return now;
    }
    void update(int now) {
        tree[now].sum = tree[tree[now].ch[0]].sum + tree[tree[now].ch[1]].sum + 1;
    }
    void push_down(int now) {
        int l = tree[now].ch[0];
        int r = tree[now].ch[1];
        tree[l].lazy ^= 1;
        tree[r].lazy ^= 1;
        swap(tree[now].ch[0], tree[now].ch[1]);
        tree[now].lazy = 0;
    }
    void split(int now, int k, int& x, int& y) {
        if (!now) {
            x = y = 0;
            return;
        }
        if (tree[now].lazy) {
            push_down(now);
        }
        if (tree[tree[now].ch[0]].sum + 1 <= k) {
            x = now;
            split(tree[now].ch[1], k - tree[tree[now].ch[0]].sum - 1, tree[now].ch[1], y);
        }
        else {
            y = now;
            split(tree[now].ch[0], k, x, tree[now].ch[0]);
        }
        update(now);
    }
    int merge(int x, int y) {
        if (!x || !y)
            return x + y;
        else {
            if (tree[x].rand < tree[y].rand) {
                if (tree[x].lazy) {
                    push_down(x);
                }
                tree[x].ch[1] = merge(tree[x].ch[1], y);
                update(x);
                return x;
            }
            else {
                if (tree[y].lazy) {
                    push_down(y);
                }
                tree[y].ch[0] = merge(x, tree[y].ch[0]);
                update(y);
                return y;
            }
        }
    }
    int kth(int now, int k) {
        while (1) {
            int l = tree[now].ch[0];
            if (k <= tree[l].sum) {
                now = l;
            }
            else if (k == tree[l].sum + 1) {
                return now;
            }
            else {
                k -= tree[l].sum + 1;
                now = tree[now].ch[1];
            }
        }
    }
    void print(int cur, ostream& out) {
        if (tree[cur].lazy == 1) {
            push_down(cur);
        }
        if (tree[cur].ch[0] != 0)
            print((tree[cur].ch[0]), out);
        out << tree[cur].val << " ";
        if (tree[cur].ch[1] != 0)
            print((tree[cur].ch[1]), out);
    }
};

splay st;

int main() {
    fcin >> n >> m;
    int x, y, l, r, p, com;
    for (int i = 1; i <= n; i++) {
        st.root = st.merge(st.root, st.new_node(i));
    }
    // st.print(st.root, fcout);
    // fcout << "\n";
    while (m--) {
        fcin >> x >> y;
        st.split(st.root, y, l, r);
        st.split(l, x - 1, l, p);
        st.tree[p].lazy ^= 1;
        st.root = st.merge(st.merge(l, p), r);
        // st.print(st.root, fcout);
        // fcout << "\n";
    }
    st.print(st.root, fcout);

    fcin.close();
    fcout.close();

    return 0;
}