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

//讲解链接： https://www.luogu.com.cn/blog/85514/fhq-treap-xue-xi-bi-ji

class splay {
public:
    class node {
    public:
        int ch[2];
        int f;
        int sum = 0; // 此节点的所有节点数
        int val = 0; //起始值设为0的时候有负值会把逻辑上为空但真实值为0的节点也算上，所以可以统一设为负值
        int rand;
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
        return now;
    }
    void update(int now) {
        tree[now].sum = tree[tree[now].ch[0]].sum + tree[tree[now].ch[1]].sum + 1;
    }
    int split(int now, int k, int& x, int& y) { // now 代表要把当前哪个节点与k比较，然后分给虚拟节点x，y。x，y代表要填哪个虚拟节点
        if (!now)
            x = y = 0;
        else {
            if (tree[now].val <= k) {
                x = now;
                split(tree[now].ch[1], k, tree[now].ch[1], y); // 如果两次都是走x的路，说明这一条原样不动的分给了x
            }
            else {
                y = now;
                split(tree[now].ch[0], k, x, tree[now].ch[0]); // 一次走x，一次走y，说明把第一次的属于x的节点右节点分给了y作为y的第一个节点
            }
            update(now);
        }
    }
    int merge(int x, int y) {
        if (!x || !y)
            return x + y;
        else {
            if (tree[x].rand < tree[y].rand) {
                tree[x].ch[1] = merge(tree[x].ch[1], y);
                update(x);
                return x;
            }
            else {
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
};

splay st;

int main() {
    fcin >> n;
    int x, y, z, a, com;
    while (n--) {
        fcin >> com >> a;
        if (com == 1) {
            st.split(st.root, a, x, y);
            st.root = st.merge(st.merge(x, st.new_node(a)), y);
        }
        else if (com == 2) {
            st.split(st.root, a, x, z);
            st.split(x, a - 1, x, y);
            y = st.merge(st.tree[y].ch[0], st.tree[y].ch[1]);
            st.root = st.merge(st.merge(x, y), z);
        }
        else if (com == 3) {
            st.split(st.root, a - 1, x, y);
            fcout << st.tree[x].sum + 1 << "\n";
            st.root = st.merge(x, y);
        }
        else if (com == 4) {
            int nn = st.kth(st.root, a);
            fcout << st.tree[nn].val << "\n";
        }
        else if (com == 5) {
            st.split(st.root, a - 1, x, y);
            int nn = st.kth(x, st.tree[x].sum);
            fcout << st.tree[nn].val << "\n";
            st.root = st.merge(x, y);
        }
        else {
            st.split(st.root, a, x, y);
            int nn = st.kth(y, 1);
            fcout << st.tree[nn].val << "\n";
            st.root = st.merge(x, y);
        }
    }

    fcin.close();
    fcout.close();

    return 0;
}
