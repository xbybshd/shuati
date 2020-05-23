/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-05-19 02:22:09
 */
#include <bits/stdc++.h>
#include <map>
#include <queue>
#include <string>

// #include <iostream>
// #include <cstring>

using namespace std;
#define MAX 1000
#define INF 0x3f3f3f3f
#define MIN 0x80000000
#define MAXF 2003
#define P 19650827
#define M 100
// int n, m, r, c, s;
// int sx, sy;
// int cnt=0;
// int root = 1;
// int maxans = 0;
// typedef long long ll;
// #define Mod 1000000007
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

int n, m, t;
int cal[MAX];
int Mod = 0;

struct st_node
{
    int l, r;
    double len = 0;
    int cnt = 0;
    st_node(){};
};

st_node st[MAX << 2];

// map<int, double> i2y;
map<double, int> y2i;
double sorty[MAX << 1];
double lastsort[MAX << 1];

int uli = 0;

void bulid(int p, int l, int r)
{
    st[p].l = l;
    st[p].r = r;
    if (l == r)
    {
        return;
    }
    int mid = (l + r) >> 1;
    bulid(p << 1, l, mid);
    bulid(p << 1 | 1, mid + 1, r);
}

void update(int p, int l, int r, int ul, int ur, int u) //在更新的时候上传当前存在的长度
{
    //总体思路，1.是否实行短路操作，是，当完全覆盖的时候就返回\
                2.是否存在延迟标记下传，否，当需要遍历到深入节点的时候，直接深入做当前的标记即可，与父节点无关，因为对\
                父节点的修改是成对的，也就是说只有涉及父节点矩形本身可以改父节点，其他的是多此一举
    if (ul <= l && ur >= r) //如果完全覆盖当前区间
    {
        st[p].cnt += u;    //就更新标记
        if (st[p].cnt > 0) //如果标记大于零就是整个线段的长度[l,r+1]
        {
            st[p].len = lastsort[r + 1] - lastsort[l];
        }
        else //否则，要么为0，要么是两个子区间和相加
        {
            if (l != r)
                st[p].len = st[p << 1].len + st[p << 1 | 1].len;
            else
                st[p].len = 0;
        }
        return;
    }

    // if (l == r)
    // {
    //     if (st[p].cnt > 0)
    //     {
    //         st[p].len = i2y[l + 1] - i2y[l];
    //     }
    //     else
    //     {
    //         st[p].len = 0;
    //     }
    //     return;
    // }
    int mid = (l + r) >> 1; //如果没有覆盖当前区间就要分区间深入
    if (ul <= mid)
    {
        update(p << 1, l, mid, ul, ur, u);
    }
    if (ur > mid)
    {
        update(p << 1 | 1, mid + 1, r, ul, ur, u);
    }
    if (st[p].cnt > 0) //分区间深入之后再更新当前存在的长度
    {
        st[p].len = lastsort[r + 1] - lastsort[l];
    }
    else
    {
        st[p].len = st[p << 1].len + st[p << 1 | 1].len;
    }
}

// double query(int p, int l, int r, int ul, int ur)
// {
//     double qlen = 0.0;
//     if (st[p].cnt > 0)
//     {
//         qlen = st[p].len;
//         return qlen;
//     }
//     if (l == r)
//         return st[p].len;
//     int mid = (l + r) >> 1;
//     // if (ul <= mid)
//     {
//         qlen += query(p << 1, l, mid, ul, ur);
//     }
//     // if (ur > mid)
//     {
//         qlen += query(p << 1 | 1, mid + 1, r, ul, ur);
//     }
//     return qlen;
// }

struct map_node
{
    double x, y1, y2, k;
    map_node()
    {
        x = y1 = y2 = k = 0;
    }
    map_node(double _x, double _y1, double _y2, double _k) : x(_x), y1(_y1), y2(_y2), k(_k){};
    bool operator<(const map_node &b)
    {
        return x < b.x;
    }
};

map_node mv[MAX];

int dicrete(int lsi)
{
    sort(sorty, sorty + lsi);
    int li = 1;
    for (int i = 0; i < lsi; i++)
    {
        if (i == 0 || sorty[i - 1] != sorty[i])
        {
            lastsort[li] = sorty[i]; //离散化的操作，排序，然后去重
            //i2y[li] = sorty[i];
            y2i[sorty[i]] = li;
            li++;
        }
    }
    return li;
}

int main()
{
    double x_1, x_2, y_1, y_2;
    n = 1;
    int ni = 1;
    while (1)
    {
        fcin >> n;
        if (n == 0)
            break;
        memset(st, 0, sizeof(st));
        i2y.clear();
        y2i.clear();
        if (n == 0)
            break;
        int mi = 0;
        int si = 0;
        for (int i = 0; i < n; i++)
        {
            fcin >> x_1 >> y_1 >> x_2 >> y_2;
            mv[mi++] = map_node(x_1, y_1, y_2, 1); //按照x的顺序，从小到大将宽(y1,y2)排序，最后一项代表是左边还是右边
            mv[mi++] = map_node(x_2, y_1, y_2, -1);
            sorty[si++] = y_1; //收集所有的y
            sorty[si++] = y_2;
        }
        int lyi = dicrete(si); //对y进行离散化处理
        sort(mv, mv + mi);
        bulid(1, 1, lyi - 1);
        double ans = 0;
        for (int i = 0; i < mi; i++)
        {
            double nx, ny1, ny2, ncnt;
            nx = mv[i].x;
            ny1 = mv[i].y1;
            ny2 = mv[i].y2;
            ncnt = mv[i].k;
            double ry1 = y2i[ny1];
            double ry2 = y2i[ny2] - 1; //更新的边是当前y前面的区间\
            因为我们更新的是点之间区间的长度而不是每个点相加的值，比如[l,r]之间的长度，是[l,l+1],...,[r-1,r]一共l-r个区间\
            相加的和，即一个点l带[l,l+1)区间的和，
            if (i > 0)
            {
                // double now_len = query(1, 1, lyi - 1, prey1, prey2);
                double now_len = st[1].len;
                ans += now_len * (nx - mv[i - 1].x);
            }
            update(1, 1, lyi - 1, ry1, ry2, ncnt);
        }
        fcout << setiosflags(ios::fixed) << setprecision(2);
        fcout << "Test case #" << ni << "\n"
              << "Total explored area: " << ans << "\n";
        ni++;
    }

    fcin.close();
    fcout.close();

    return 0;
}
