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
int dpp[MAX][2] = {0};
int fa[MAX]={0};
int ru[MAX] = {0};
int cnt=0;
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

struct edge{
    int to,pre;
    edge(){};
};

edge emu[MAX];

void add_e(int u,int v){//链式前向星加边
    emu[++cnt].to=v;
    emu[cnt].pre=head[u];
    head[u]=cnt;
}

void dfs(int ni){//递归深搜
    dpp[ni][1]+=val[ni];//先序遍历的，如果去的话加上去舞会的值
    for(int i=head[ni];i;i=emu[i].pre){
        int qqq = 1;
        int vi = emu[i].to;
        dfs(vi);
        dpp[ni][1] += dpp[vi][0]; //上司1区，下属只能不去，加上dp[0][1];
        dpp[ni][0]+=max(dpp[vi][0],dpp[vi][1]);//上司不去，加上下属去或者不去的最大值
    }
}

stack<int> ss;

void nodfs(int ni){//非递归深搜
    ss.push(ni);//根节点入栈
    while(!ss.empty()){
        int u = ss.top();
        if(vis[u]==1){//子节点入栈但是没有访问完子节点的为1
            vis[u] = 2;//访问到为1的节点，说明子节点已经全部访问完
            dpp[fa[u]][1]+=dpp[u][0];//此节点u的dpp值已经全部算完，可以加入其父亲的
            dpp[fa[u]][0]+=max(dpp[u][0],dpp[u][1]);
            ss.pop();
        }
        else if(vis[u]==0){
            vis[u] = 1;//首次访问设为1
            dpp[u][1]+=val[u];//其去舞会的值可以提前加上
            for (int i = head[u]; i;i=emu[i].pre){
                int vi = emu[i].to;
                ss.push(vi);//所有子节点入栈
            }
        }
    }
}

queue<int> que;

void topsort(){
    while(!que.empty()){//队列中全部都是入度为0的
        int u = que.front();
        que.pop();
        dpp[u][1] += val[u];
        dpp[fa[u]][1]+=dpp[u][0];
        dpp[fa[u]][0]+=max(dpp[u][0],dpp[u][1]);
        ru[fa[u]]--;
        if(ru[fa[u]]==0){
            que.push(fa[u]);
        }
    }
}

int main()
{
    int ni = 1;
    fcin>>n;
    for(int i=1;i<=n;i++){
        fcin>>val[i];
    }
    for(int i=1;i<=n;i++){
        int a,b;
        fcin>>a>>b;
        fa[a]=b;
        ru[b]++;
        add_e(b,a);
    }
    int root = 0;
    for(int i=1;i<=n;i++){
        if(fa[i]==0){
            //dfs(i);
            // nodfs(i);
            // fcout<<max(dpp[i][0],dpp[i][1]);
            root = i;
            //break;
        }
        if(ru[i]==0){
            que.push(i);
        }
    }
    topsort();
    fcout<<max(dpp[root][0],dpp[root][1]);

    fcin.close();
    fcout.close();

        return 0;
}