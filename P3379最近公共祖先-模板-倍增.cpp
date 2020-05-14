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
#define MAX 500//010
#define INF 0x3f3f3f3f
#define MAXF 12000
#define P 19650827
int n, m, r, c, s;
int sx, sy;
int cnt=0;
int root = 1;
int maxans = 0;
typedef unsigned long long ull;
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

struct edge{
    int to, pre;
    edge(){};
};

edge emu[MAX<<1];
int head[MAX] = {0};
void add(int u,int v){
    emu[++cnt].to = v;
    emu[cnt].pre = head[u];
    head[u] = cnt;
}

int fa[MAX][22] = {0};
int lg[MAX] = {0};
int depth[MAX] = {0};
void dfs(int ni,int fath){//深搜一遍，确定每个节点的第2^k个祖先，和这个节点的深度
    fa[ni][0] = fath;//第2^0个祖先是它的上一个
    depth[ni] = depth[fath] + 1;//它的深度是父亲深度加1，因为是深搜所以必然父节点深度已知
    for (int i = 1; i <= lg[depth[ni]];i++){
        fa[ni][i] = fa[fa[ni][i - 1]][i - 1];//ni的第2^i个父亲等于它的第2^i-1个父亲节点的第2^i-1个父亲节点
    }
    for (int i = head[ni]; i;i=emu[i].pre){
        int vi = emu[i].to;
        if(vi!=fath)//父节点就不要深搜了
        dfs(vi, ni);
    }
}

int LCA(int x,int y){
    if(depth[x]<depth[y]){
        swap(x, y);//假设x深度大于y的深度，如果不是就交换
    }
    while(depth[x]>depth[y]){
        x = fa[x][lg[depth[x] - depth[y]]];//把x拉到和y一样高，对数向上爬，相当于二分
    }
    if(x==y)
        return x;//如果拉到一样高的时候已经重合，直接返回
    for (int k = lg[depth[x]]; k >= 0;k--){//从x的最大深度对数开始枚举
        if(fa[x][k]!=fa[y][k]){//x和y相等说明枚举大了，不相等说明在公共祖先下面
            x = fa[x][k];//让xy等于枚举的下面的节点
            y = fa[y][k];
        }
    }//最终会到公共祖先的下一个节点
    return fa[x][0];//返回父节点
}

int main()
{
    fcin >> n >> m >> s;
    for (int i = 1; i <= n-1;i++){
        int u, v;
        fcin >> u >> v;
        add(u, v);//树要双相加边
        add(v, u);
    }
    int a = 0 << 1;
    for (int i = 1; i <= n;i++){//求i的对数的方法，只是所有对数要-1
        lg[i] = (lg[i - 1] + (1 << lg[i - 1]== i));//前一个数的对数代表下一个将要到达的2^i值
        lg[i - 1]--;
    }
    lg[0] = 0;
    lg[n]--;
    dfs(s, 0);
    for (int i = 1; i <= m;i++){
        int mx, my;
        fcin >> mx >> my;
        int ans = LCA(mx, my);
        fcout << ans << endl;
    }

        fcin.close();
    fcout.close();

        return 0;
}