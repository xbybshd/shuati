#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 10020
#define INF 0x1000000
#define MAXF 0x3f3f3f3f
int n, m, r, c;
int sx, sy;
int u, v;
int fa[MAX] = {0};
int rk[MAX] = {0};

int find_b(int x)
{
    while (x != fa[x])
        x = fa[x] = fa[fa[x]];
    return x;
}

int find_br(int x)
{
    if (x == fa[x])
        return x;
    return fa[x] = find_br(fa[x]);
}

int main()
{

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        fa[i] = i;
        rk[i] = 1;
    }

    while (m--)
    {
        int z, x, y;
        cin >> z >> x >> y;
        int a = find_b(x);
        int b = find_b(y);
        if (z == 1)
        {
            if (rk[a] < rk[b])
                fa[a] = b;
            else if (rk[a] > rk[b])
                fa[b] = a;
            else
            {
                fa[a] = b;
                rk[b]++;
            }
        }
        else
        {

            cout << (a == b ? "Y\n" : "N\n");
        }
    }

    return 0;
}