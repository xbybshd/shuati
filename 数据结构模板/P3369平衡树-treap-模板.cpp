/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 100050

const int INF = 0x7fffffff;

#define Mod 1000000007

using inll = unsigned long long;
inll n, m, k;
#define Mod 1000000007
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

struct Treap {
    struct node {
        int left;
        int right;
        int val;
        int size;
        int data;
        int recv;
    };
    node tree[MAX];
    int cnt;
    int root;
    void update(int x) {
        tree[x].size = tree[tree[x].left].size + tree[tree[x].right].size + tree[x].recv;
    }

    void right_rotate(int& now) {
        int temp = tree[now].left;
        tree[now].left = tree[temp].right;
        tree[temp].right = now;
        tree[temp].size = tree[now].size;
        update(now);
        now = temp;
    }

    void left_rotate(int& now) {
        int temp = tree[now].right;
        tree[now].right = tree[temp].left;
        tree[temp].left = now;
        tree[temp].size = tree[now].size;
        update(now);
        now = temp;
    }

    void insert(int& now, int data) {
        if (now == 0) {
            now = ++cnt;
            tree[now].size = 1;
            tree[now].data = data;
            tree[now].val = rand() * rand() % 19620817;
            tree[now].recv = 1;
            return;
        }
        tree[now].size++;
        if (tree[now].data == data) {
            tree[now].recv++;

            return;
        }
        else if (tree[now].data > data) {
            insert(tree[now].left, data);
        }
        else {
            insert(tree[now].right, data);
        }

        if (tree[now].left != 0 && tree[tree[now].left].val < tree[now].val) {
            right_rotate(now);
        }
        if (tree[now].right != 0 && tree[tree[now].right].val < tree[now].val) {
            left_rotate(now);
        }
        update(now);
    }

    void erase(int& now, int data) {
        tree[now].size--;
        if (tree[now].data == data) {
            if (tree[now].recv > 1) {
                tree[now].recv--;
                return;
            }
            if (tree[now].left == 0 && tree[now].right == 0) {
                now = 0;
                return;
            }
            if (tree[now].left == 0 || tree[now].right == 0) {
                now = tree[now].left + tree[now].right;
                return;
            }
            if (tree[tree[now].left].val < tree[tree[now].right].val) {
                right_rotate(now);
                erase(tree[now].right, data);
                return;
            }
            else {
                left_rotate(now);
                erase(tree[now].left, data);
            }
        }
        else if (tree[now].data >= data) {
            erase(tree[now].left, data);
        }
        else {
            erase(tree[now].right, data);
        }
        update(now);
    }

    int rank(int now, int data) {
        if (now == 0) {
            return 0;
        }
        if (tree[now].data == data) {
            return tree[tree[now].left].size + 1;
        }
        else if (tree[now].data > data) {
            return rank(tree[now].left, data);
        }
        else {
            return tree[tree[now].left].size + tree[now].recv + rank(tree[now].right, data);
        }
    }

    int acrank(int now, int r) {
        if (now == 0) {
            return 0;
        }
        int minus = tree[now].size - tree[tree[now].right].size;
        if (r > tree[tree[now].left].size && r <= minus) {
            return tree[now].data;
        }
        if (r <= tree[tree[now].left].size) {
            return acrank(tree[now].left, r);
        }
        else {
            r = r - minus;
            return acrank(tree[now].right, r);
        }
    }

    int upper(int now, int data) {
        int ans = INF;
        while (now) {
            if (data < tree[now].data && tree[now].data < ans) {
                ans = tree[now].data;
            }
            if (data < tree[now].data) {
                now = tree[now].left;
            }
            else {
                now = tree[now].right;
            }
        }
        return ans;
    }

    int lower(int now, int data) {
        int ans = -INF;
        while (now) {
            if (data > tree[now].data && tree[now].data > ans) {
                ans = tree[now].data;
            }
            if (data > tree[now].data) {
                now = tree[now].right;
            }
            else {
                now = tree[now].left;
            }
        }
        return ans;
    }
};

Treap st;

int main()
{
    fcin >> m;
    int qq = m;
    while (m--) {
        int op, u;
        fcin >> op >> u;
        int rr = qq - m;
        if (op != 1 && op != 2) fcout << (qq - m) << "  ";
        if (op == 1) {
            st.insert(st.root, u);
        }
        else if (op == 2) {
            st.erase(st.root, u);
        }
        else if (op == 3) {
            int r;
            r = st.rank(st.root, u);
            fcout << r << endl;
        }
        else if (op == 4) {
            int r;
            r = st.acrank(st.root, u);
            fcout << r << endl;
        }
        else if (op == 5) {
            int r;
            r = st.lower(st.root, u);
            fcout << r << endl;
        }
        else {
            int r;
            r = st.upper(st.root, u);
            fcout << r << endl;
        }
    }



    fcin.close();
    fcout.close();

    return 0;
}