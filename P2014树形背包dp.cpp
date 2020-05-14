/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include<bits/stdc++.h>
#include <queue>
#include <map>
// #include <iostream>
// #include <cstring>

using namespace std;
#define MAX 6010
#define INF 0x3f3f3f3f
#define MAXF 400
int n, m, r, c, s;
int sx, sy;
int val[MAX] = {0};
int head[MAX]={0};
int vis[MAX] = {0};
int dpp[MAX][MAX] = {0};
int fa[MAX]={0};
int ru[MAX] = {0};
int cnt=0;
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

struct edge{
    int to, pre;
    edge(){};
};

edge emu[MAX];

void add_e(int u,int v){
    emu[++cnt].to=v;
    emu[cnt].pre=head[u];
    head[u]=cnt;
}

void dfs(int ni){
    dpp[ni][1] = val[ni];
    for (int i = head[ni]; i;i=emu[i].pre){//遍历每个子节点
        int vi = emu[i].to;
        dfs(vi);     //先对每个节点dfs-dp，再对总结点dp
        int u = emu[i].to;
        int j ;//因为取了0节点，所以在算0节点的时候m要+1
        for (j= (ni == 0 ? m + 1 : m); j > 0;j--){//以当前ni为根节点，加入j门课时，最大分数,在当前子节点数不足j时，会有\
        非零值填入，但是绝对不会大于j-k和k都存在的情况，所以可以放心dp，并且当前节点返回的时候，父节点的dp只关心最大的那个值
            for (int k = 0; k < j;k++){//类似于区间dp一样将已经取得的j进行分割
                dpp[ni][j] = max(dpp[ni][j], dpp[ni][j - k] + dpp[u][k]);
            }
        }
    }
}


int main()
{
    int ni = 1;
    fcin >> n >> m;
    for (int i = 1; i <= n;i++){
        int prec, weg;
        fcin >> prec >> weg;
        add_e(prec, i);
        val[i] = weg;
    }
    dfs(0);
    fcout << dpp[0][m+1];

    fcin.close();
    fcout.close();

        return 0;
}