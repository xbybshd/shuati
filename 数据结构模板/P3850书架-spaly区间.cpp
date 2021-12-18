/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 100

const int INF = 0x7fffffff;

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
        int sum = 0;
        int val = -INF; //起始值设为0的时候有负值会把逻辑上为空但真实值为0的节点也算上，所以可以统一设为负值
        string str;
        int recv;
        node() {};
        node(int _val)
            : val(_val) {
            recv = sum = 1;
        }
    };
    node tree[MAX];
    int recyle[MAX];
    int cnt, points, recy;
    int root = 0;

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

    int newnode(int v, int f, const string& str) {
        cnt++;
        tree[cnt].val = v;
        tree[cnt].f = f;
        tree[cnt].sum = tree[cnt].recv = 1;
        tree[cnt].str = str;
        return cnt;
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

    void destory(int x) {
        tree[x].ch[0] = tree[x].ch[1] = tree[x].f = tree[x].recv = tree[x].sum = 0;
        tree[x].val = -INF;
        if (x == cnt)
            cnt--;
        // if (points == 0)
        //     cnt = 0;
    }

    int getroot() {
        return root;
    }

    int find(int v) {
        v += 2; //权值，或者说顺序为0的节点，他自己的recv也是为1的，所以当v的顺序是从0开始的时候，在查权值之前要加1
        int now = root;
        while (1) {
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

    int build(int v, const string& str) { // v代表要插入节点的权值，此题中开始建树是按照给定权值来建树，之后find都是按照二叉树顺序来查找
        points++;
        if (root == 0) { //只有根节点为0时，代表除了最初节点之外，所有的节点都没了。有两种情况，\
        1，最开始的时候，2，删除操作把所有的节点都删除时
            root = 1;
            tree[0].ch[0] = newnode(v, 0, str);
            return cnt;
        }
        else {
            int now = root;
            while (1) {
                tree[now].sum++;
                if (v == tree[now].val) {
                    tree[now].recv++;
                    return now;
                }
                int next = tree[now].val < v ? 1 : 0;
                if (!tree[now].ch[next]) {
                    tree[now].ch[next] = newnode(v, now, str);
                    return cnt;
                }
                now = tree[now].ch[next];
            }
        }
        return 0;
    }

    void push(int v, const string& str) {
        int add = build(v, str);
        splay_ro(add, 0);
    }

    void insert(int k, const string& str) {
        int kth = find(k);
        splay_ro(kth, 0);
        int k_left = find(k - 1);
        splay_ro(k_left, kth);
        tree[k_left].ch[1] = newnode(100, k_left, str);
        update(k_left);
        update(kth);
    }

    int acrank(int r) {
        r += 2; //v只能从1开始
        int now = root;
        // if (r > points)
        //     return -INF;
        while (1) {
            int minus = tree[now].sum - tree[tree[now].ch[1]].sum;
            if (r > tree[tree[now].ch[0]].sum && r <= minus)
                break;
            if (r < minus) {
                now = tree[now].ch[0];
            }
            else {
                r = r - minus;
                now = tree[now].ch[1];
            }
        }
        splay_ro(now, 0); //每次找排名节点要旋转一次
        return now;
    }
};

splay st;

int main() {
    fcin >> n;
    st.push(-1, "");
    for (int i = 1; i <= n; i++) {
        string str;
        fcin >> str;
        st.push(i, str);
    }
    fcin >> m;
    while (m--) {
        string str1;
        int b;
        fcin >> str1 >> b;
        st.insert(b, str1);
    }
    int p;
    fcin >> p;
    while (p--) {
        int c;
        fcin >> c;
        int ans = st.acrank(c);
        fcout << st.tree[ans].str << "\n";
    }

    fcin.close();
    fcout.close();

    return 0;
}