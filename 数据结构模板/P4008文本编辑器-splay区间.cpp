/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 2100000

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
        char ca;
        node() {};
    };
    node tree[MAX];
    int recyle[MAX];
    char val_idx[MAX];
    int cnt, points, recy, num, gb;
    int root = 0;

    void update(int x) {
        if (x) {
            int l = tree[x].ch[0];
            int r = tree[x].ch[1];
            tree[x].sum = tree[tree[x].ch[0]].sum + tree[tree[x].ch[1]].sum + 1;
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

    int newnode(char v, int fa) {
        int now;
        if (recy) {
            now = recyle[recy--];
        }
        else {
            now = ++cnt;
        }
        tree[now].ch[0] = tree[now].ch[1] = 0;
        tree[now].ca = v;
        tree[now].f = fa;
        tree[now].sum = 1;
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
            //push_down(now);
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
        if (l > r)
            return 0;
        int mid = (l + r) >> 1; //标签从0开始建树，先建立的节点去中间
        int c_num = newnode(val_idx[mid], fa);
        if (l < mid)
            tree[c_num].ch[0] = build(l, mid - 1, c_num);
        if (r > mid)
            tree[c_num].ch[1] = build(mid + 1, r, c_num);
        update(c_num); //建完节点之后一定要update
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
        int l = find(x);
        int r = find(x + y + 1);
        splay_ro(l, 0);
        splay_ro(r, l);
        erase(tree[r].ch[0]);
        num -= y;
        tree[r].ch[0] = 0;
        update(r);
        update(l);
    }

    void print_val(int x, ostream& out) {
        if (tree[x].ch[0]) {
            print_val(tree[x].ch[0], out);
        }
        out << tree[x].ca;
        if (tree[x].ch[1]) {
            print_val(tree[x].ch[1], out);
        }
    }

    void print(int x, int y, ostream& out) {
        int l = find(x);
        int r = find(x + y + 1);
        splay_ro(l, 0);
        splay_ro(r, l);
        int p = tree[r].ch[0];
        print_val(p, out);
    }
};

splay st;

int main() {
    fcin >> n;
    st.val_idx[1] = 0;
    st.val_idx[2] = 0;
    st.root = st.build(1, 2, 0);
    st.num = 2;
    while (n--) {
        string str;
        fcin >> std::skipws >> str;
        if (str[0] == 'M') {
            int a;
            fcin >> a;
            st.gb = a;
        }
        else if (str[0] == 'P') {
            st.gb--;
        }
        else if (str[0] == 'N') {
            st.gb++;
        }
        else if (str[0] == 'I') {
            int a;
            fcin >> a;
            for (int i = 1; i <= a; i++) {
                char cc;
                fcin >> std::noskipws >> cc;
                if (cc == '\n' || cc == '\r') {
                    i--;
                    continue;
                }
                st.val_idx[i] = cc;
            }
            st.insert(st.gb, a);
        }
        else if (str[0] == 'D') {
            int a;
            fcin >> a;
            st.del(st.gb, a);
        }
        else {
            int a;
            fcin >> a;
            st.print(st.gb, a, fcout);
            fcout << '\n';
        }
    }

    fcin.close();
    fcout.close();

    return 0;
}