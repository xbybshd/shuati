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
        int recv;
        node() {};
        node(int _val)
            : val(_val) {
            recv = sum = 1;
        }
    };
    node tree[MAX];
    int cnt, points;
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

    int newnode(int v, int f) {
        cnt++;
        tree[cnt].val = v;
        tree[cnt].f = f;
        tree[cnt].sum = tree[cnt].recv = 1;
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
        int now = root;
        while (1) {
            if (tree[now].val == v) {
                splay_ro(now, 0);
                return now;
            }
            int next = tree[now].val < v ? 1 : 0;
            if (tree[now].ch[next] == 0)
                return 0;
            now = tree[now].ch[next];
        }
    }

    int build(int v) { // v代表要插入节点的权值，
        points++;
        if (root == 0) { //只有根节点为0时，代表除了最初节点之外，所有的节点都没了。有两种情况，\
        1，最开始的时候，2，删除操作把所有的节点都删除时
            root = 1;
            tree[0].ch[0] = newnode(v, 0);
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
                    tree[now].ch[next] = newnode(v, now);
                    return cnt;
                }
                now = tree[now].ch[next];
            }
        }
        return 0;
    }

    void push(int v) {
        int add = build(v);
        splay_ro(add, 0);
    }

    void pop(int v) {
        int del = find(v); //找到要删除的节点，在查找过程中会将要删除的旋转到根节点
        if (!del)
            return;
        points--;
        if (tree[del].recv > 1) {
            tree[del].recv--;
            tree[del].sum--;
            return;
        }
        if (!tree[del].ch[0]) { //如果没有左子树，直接将右子树接在根节点上
            root = tree[del].ch[1];
            tree[root].f = 0;
        }
        else { //如果有左子树，找到其前驱，将其旋转到左子树的位置上，(它必然没有右子树)，然后将要删除节点的右子树接到前驱右节点上，\
                      再将前驱接到超级根节点上，最后更新新的根节点，就是前驱
            int lef = tree[del].ch[0];
            while (tree[lef].ch[1])
                lef = tree[lef].ch[1];
            splay_ro(lef, del);
            int rig = tree[del].ch[1];
            connect(rig, lef, 1);
            connect(lef, 0, 1);
            root = lef;
            update(lef);
        }
        destory(del);
    }

    int rank(int v) {
        int ans = 0, now = root;
        while (1) {
            if (tree[now].val == v) {
                ans = ans + tree[tree[now].ch[0]].sum + 1; //如果当前节点与要找的节点值一样，那么排名就是左子树的sum+1
                break;
            }
            if (now == 0)
                return 0;
            if (tree[now].val > v) {
                now = tree[now].ch[0];
            }
            else {
                ans = ans + tree[tree[now].ch[0]].sum + tree[now].recv;
                now = tree[now].ch[1];
            }
        }
        if (now)
            splay_ro(now, 0);
        return ans;
    }

    int acrank(int r) {
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
        splay_ro(now, 0);
        return tree[now].val;
    }

    int upper(int v) { //这个是从根节点开始，给定值，求值的后继，而不是给定节点位置求其后继，这个就直接用二分查找即可
        int ans = INF;
        int now = root;
        while (now) {
            if (tree[now].val > v && tree[now].val < ans) {
                ans = tree[now].val;
            }
            if (tree[now].val > v) { //注意如果当前点大于要求的值v，那么找左子树，小于等于都是右子树，因为求得是后继，等于的时候也要走右子树
                now = tree[now].ch[0];
            }
            else {
                now = tree[now].ch[1];
            }
        }
        return ans;
    }

    int lower(int v) {
        int ans = -INF;
        int now = root;
        while (now) {
            if (tree[now].val < v && tree[now].val > ans) {
                ans = tree[now].val;
            }
            if (tree[now].val < v) { //求得是前驱当前值大于要求值就走右子树，小于等于走左子树
                now = tree[now].ch[1];
            }
            else {
                now = tree[now].ch[0];
            }
        }
        return ans;
    }
};

splay st;

int main() {
    fcin >> m;
    int qq = m;
    int i = 2;
    while (m--) {
        int op, u;
        fcin >> op >> u;
        cout << i << " " << op << " " << u << "\n";
        i++;
        if (op == 1) {
            st.push(u);
        }
        else if (op == 2) {
            st.pop(u);
        }
        else if (op == 3) {
            int r;
            r = st.rank(u);
            fcout << r << endl;
        }
        else if (op == 4) {
            int r;
            r = st.acrank(u);
            fcout << r << endl;
        }
        else if (op == 5) {
            int r;
            r = st.lower(u);
            fcout << r << endl;
        }
        else {
            int r;
            r = st.upper(u);
            fcout << r << endl;
        }
    }

    fcin.close();
    fcout.close();

    return 0;
}