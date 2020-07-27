/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:37:09
 */
#include <bits/stdc++.h>
#include <queue>
#include <map>

using namespace std;
#define MAX 500
#define INF 0x3f3f3f3f
#define MAXF 2010
int n, m, r, c, s;
int sx, sy;
int ss1[MAX] = {0};
int ss2[MAX] = {0};
int cal[MAX] = {0};
int up[MAX] = {0};

ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

int max_t(int a, int b, int c)
{
    int x = a > b ? a : b;
    int y = x > c ? x : c;
    return y;
};
map<int, int> num_pos;

int find_bigger(int l, int r, int val)
{
    int mid;
    while (l < r)
    {
        mid = (l + r) >> 1;
        if (up[mid] <= val)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    return l;
}

int main()
{

    fcin >> n;
    for (int i = 0; i < n; i++)
    {
        fcin >> ss1[i];
        num_pos[ss1[i]] = i;
    }
    for (int i = 0; i < n; i++)
    {
        fcin >> ss2[i];
        cal[num_pos[ss2[i]]] = i;
    }
    int ui = 1;
    int wi = 0;
    int ws = 0;
    up[0] = cal[0];
    for (ui = 1; ui < n; ui++)
    {
        int wi = find_bigger(0, ws + 1, cal[ui]);
        if (wi > ws)
            ws++;
        up[wi] = cal[ui];
    }
    fcout << ws + 1;

    fcin.close();
    fcout.close();

    return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int N = 1000 + 10;
int x[N], y[N], dp[N][N];

int main()
{
    string a, b;
    cin >> a >> b;
    int lena = a.length(), lenb = b.length();

    for (int i = 1; i <= lena; i++)
    {
        for (int j = 1; j <= lenb; j++)
        {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
            {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }

    cout << dp[lena][lenb] << endl;

    return 0;
}