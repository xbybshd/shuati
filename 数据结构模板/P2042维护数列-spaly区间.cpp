/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 300

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
        int val_sum; // 此节点的权值和
        int max_sum; // 此节点的最大子串和
        int lazy; // 改变此节点子树值的lazy数值
        int laz; //是否改变了值的lazy标记
        int recv; //翻转lazy标记
        int left_sum; // 以最左边为起点的最大子串和
        int right_sum; //以最右边为起点的最大子串和
        node() {};
    };
    node tree[MAX];
    int recyle[MAX];
    int val_idx[MAX];
    int cnt, points, recy, num;
    int root = 0;

    void update(int x) {
        if (x) {
            int l = tree[x].ch[0];
            int r = tree[x].ch[1];
            tree[x].sum = tree[tree[x].ch[0]].sum + tree[tree[x].ch[1]].sum + 1;
            tree[x].val_sum = tree[l].val_sum + tree[r].val_sum + tree[x].val;
            tree[x].left_sum = max(tree[l].left_sum, tree[l].val_sum + tree[x].val + tree[r].left_sum);
            tree[x].right_sum = max(tree[r].right_sum, tree[r].val_sum + tree[x].val + tree[l].right_sum);
            tree[x].max_sum = max(max(tree[l].max_sum, tree[r].max_sum), tree[l].right_sum + tree[x].val + tree[r].left_sum);
        }
    }

    void push_down(int x) {
        int l = tree[x].ch[0];
        int r = tree[x].ch[1];
        //以下节点一定要判断是不是0，不要把0节点给更新掉了
        if (tree[x].laz) {
            tree[x].lazy = tree[x].laz = 0;
            if (l) {
                tree[l].laz = true;
                tree[l].val = tree[x].val;
                tree[l].val_sum = tree[x].val * tree[l].sum;
            }
            if (r) {
                tree[r].laz = true;
                tree[r].val = tree[x].val;
                tree[r].val_sum = tree[x].val * tree[r].sum;
            }
            if (tree[x].val >= 0) {
                if (l) {
                    tree[l].left_sum = tree[l].right_sum = tree[l].max_sum = tree[l].val_sum;
                }
                if (r) {
                    tree[r].left_sum = tree[r].right_sum = tree[r].max_sum = tree[r].val_sum;
                }
            }
            else {
                if (l) {
                    tree[l].left_sum = tree[l].right_sum = 0;
                    tree[l].max_sum = tree[x].val;
                }
                if (r) {
                    tree[r].left_sum = tree[r].right_sum = 0;
                    tree[r].max_sum = tree[x].val;
                }
            }
        }
        if (tree[x].recv) {
            tree[x].recv = 0;
            if (l) {
                tree[l].recv ^= 1;
                swap(tree[l].ch[0], tree[l].ch[1]);
                swap(tree[l].left_sum, tree[l].right_sum);
            }
            if (r) {
                tree[r].recv ^= 1;
                swap(tree[r].ch[0], tree[r].ch[1]);
                swap(tree[r].left_sum, tree[r].right_sum);
            }
        }
    }

    int identify(int x) {
        return tree[tree[x].f].ch[0] == x ? 0 : 1;
    }

    void connect(int x, int father, int son) {
        tree[x].f = father;
        tree[father].ch[son] = x;
    }

    void rotate(int x) { //旋转一个节点，这种写法就不会区分是左旋还是右旋
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

    int newnode(int v, int fa) {
        int now;
        if (recy) {
            now = recyle[recy--];
        }
        else {
            now = ++cnt;
        }
        tree[now].ch[0] = tree[now].ch[1] = 0;
        tree[now].val = tree[now].max_sum = v;
        tree[now].left_sum = tree[now].right_sum = max(0, v);
        tree[now].f = fa;
        tree[now].sum = 1;
        tree[now].recv = tree[now].lazy = tree[now].laz = 0;
        if (fa == 0) {
            tree[0].ch[0] = now;
            root = now;
        }

        return now;
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

    int find(int v) {
        v += 1; //权值，或者说顺序为0的节点，他自己的recv也是为1的，所以当v的顺序是从0开始的时候，在查权值之前要加1
        int now = root;
        while (1) {
            push_down(now);
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

    int build(int l, int r, int fa) { // v代表要插入节点的权值，
        if (l > r)//区间建树，只要标出l>r的情况
            return 0;
        int mid = (l + r) >> 1; //标签从0开始建树，先建立的节点去中间
        int c_num = newnode(val_idx[mid], fa);
        if (l < mid)
            tree[c_num].ch[0] = build(l, mid - 1, c_num);
        if (r > mid)
            tree[c_num].ch[1] = build(mid + 1, r, c_num);
        update(c_num);
        return c_num;
    }

    void insert(int k, int x) {
        int l = find(k);
        int r = find(k + 1);
        splay_ro(l, 0);
        splay_ro(r, l);
        tree[r].ch[0] = build(1, x, r);
        num += x;
        update(r);
        update(l);
    }

    void erase(int k) {
        if (!k)
            return;
        recyle[++recy] = k;
        erase(tree[k].ch[0]);
        erase(tree[k].ch[1]);
    }

    void del(int x, int y) {
        int l = find(x - 1);
        int r = find(x + y);
        splay_ro(l, 0);
        splay_ro(r, l);
        erase(tree[r].ch[0]);
        num -= y;
        tree[r].ch[0] = 0;
        update(r);
        update(l);
    }

    void make_same(int x, int y, int v) {
        int l = find(x - 1);
        int r = find(x + y);
        splay_ro(l, 0);
        splay_ro(r, l);
        int ms = tree[r].ch[0];
        tree[ms].val = v;
        tree[ms].val_sum = tree[ms].sum * v;
        if (v <= 0) {
            tree[ms].left_sum = tree[ms].right_sum = 0;
            tree[ms].max_sum = v;
        }
        else {
            tree[ms].left_sum = tree[ms].right_sum = tree[ms].max_sum = tree[ms].sum * v;
        }
        tree[ms].lazy = v;
        tree[ms].laz = true;
        update(r);
        update(l);
    }

    void reverse(int x, int y) {
        int l = find(x - 1);
        int r = find(x + y);
        splay_ro(l, 0);
        splay_ro(r, l);
        int re = tree[r].ch[0];
        if (!tree[re].laz) {
            tree[re].recv ^= 1;
            swap(tree[re].ch[0], tree[re].ch[1]);
            swap(tree[re].left_sum, tree[re].right_sum);
            update(r);
            update(l);
        }
    }

    int query_sum(int x, int y) {
        int l = find(x - 1);
        int r = find(x + y);
        splay_ro(l, 0);
        splay_ro(r, l);
        int re = tree[r].ch[0];
        return tree[re].val_sum;
    }

    int query_max() {
        // int l = find(0);
        // int r = find(num + 1);
        // splay_ro(l, 0);
        // splay_ro(r, l);
        // int re = tree[r].ch[0];
        // update(re);
        return tree[root].max_sum;
    }
};

splay st;

int main() {
    fcin >> n >> m;
    st.val_idx[1] = -INF;
    for (int i = 1; i <= n; i++) {
        fcin >> st.val_idx[i + 1];
    }
    st.val_idx[n + 2] = -INF;
    st.num = n;
    st.tree[0].max_sum = -INF;//这三个一定要设为最小
    st.root = st.build(1, n + 2, 0);
    int k = 3;
    while (m--) {
        string s1;
        fcin >> s1;
        cout << k << '\n';
        if (s1[0] == 'I') {
            int a, b;
            fcin >> a >> b;
            for (int i = 1; i <= b; i++) {
                fcin >> st.val_idx[i];
            }
            st.insert(a, b);
        }
        else if (s1[0] == 'D') {
            int a, b;
            fcin >> a >> b;
            st.del(a, b);
        }
        else if (s1[2] == 'K') {
            int a, b, c;
            fcin >> a >> b >> c;
            st.make_same(a, b, c);
        }
        else if (s1[0] == 'R') {
            int a, b;
            fcin >> a >> b;
            st.reverse(a, b);
        }
        else if (s1[0] == 'G') {
            int a, b;
            fcin >> a >> b;
            int aab = st.query_sum(a, b);
            fcout << aab << "\n";
        }
        else {
            int aa = st.query_max();
            fcout << aa << "\n";
            //fcout << st.query_max() << "\n";
        }
        k++;
    }

    fcin.close();
    fcout.close();

    return 0;
}