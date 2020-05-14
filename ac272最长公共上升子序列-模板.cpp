/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include<bits/stdc++.h>
#include <queue>
#include <map>

using namespace std;
#define MAX 300
#define INF 0x3f3f3f3f
#define MAXF 2010
int n, m, r, c, s;
int sx, sy;
int sa1[MAX];
int sa2[MAX];
int dpp[MAX][MAX] = {0};

ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);


int max_t(int a,int b,int c){
    int x = a > b ? a : b;
    int y = x > c ? x : c;
    return y;
};


int main()
{

    fcin >> n;
    for (int i = 1; i <= n;i++){
        fcin >> sa1[i];
    }
    for (int i = 1; i <= n;i++){
        fcin >> sa2[i];
    }
    int maxn;
    int ans = 0;
    for (int i = 1; i <= n;i++){//dpp[i][j]代表以sa2[j]为结尾的最长公共上升子串长度
        maxn = 0;
        for (int j = 1; j <= n;j++){
            if(sa1[i]==sa2[j])
                dpp[i][j] = maxn + 1;
            else
                dpp[i][j] = dpp[i - 1][j];//如果i!=j，那么有没有sa1[i]并不影响
            if(sa1[i]>sa2[j])
                maxn = max(maxn, dpp[i - 1][j]);//这里的最大值是要找出i-1时，在当前j之前，所有i=j时dpp中的最大长度数值，只有当当前i大于\
                某个j时，讨论最大值才有意义，如果在之后的某个j中，i=j,那么他们是从之前某个最大的i-1,j中转移过来，并且那个j应该小于现在的i
        }
    }
    for (int i = 1; i <= n;i++){
        ans = dpp[n][i] > ans ? dpp[n][i] : ans;
    }
        fcout << ans;

    fcin.close();
    fcout.close();

        return 0;
}