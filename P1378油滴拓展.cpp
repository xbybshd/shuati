#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 10020
#define INF 0x3f3f3f3f
#define MAXF 500020
int n, m, r, c, s;
int sx, sy;
int u, v;
double x_1,y_1, x_2, y_2;
double lx, ly, rx, ry;
int vec_len;
double vetx[6][2] = {0};
double dist[6][10] = {0};
double maxs = 0;
double elems = 0;
int vis[10] = {0};
double min_raid[6] = {0};

double min_vl(double* dis,int ni){
    double mine = INF;
    for (int i = 0; i < vec_len+n;i++){
        if(i==ni||!vis[i])
            continue;
        mine = min(dis[i], mine);
    }
    return mine;
}

void dfs(int ni,int nv){
        vis[ni] = 1;
    double raid = min_vl(dist[ni],ni);
    int local[6] = {0};//如果保存状态在回复不太容易，就直接开一个局部状态数组，标记修改过的
    for (int i = 0; i < vec_len;i++){
            if(i!=ni&&!vis[i]){
            local[i]=1;
            double ld=dist[ni][i];
            dist[ni][i] -= raid;
            dist[i][ni] -= raid;
            if(dist[ni][i]<=0&&ld>0&&i<n){
                vis[i] = 1;
                nv++;
            }
        }
    }
    min_raid[ni] = raid;
    if(nv==n){
        elems = 0;
        for (int i = 0; i < n;i++){
            elems += min_raid[i] * min_raid[i];
        }
      //  elems *= M_PI;
        maxs = max(elems, maxs);
        
        min_raid[ni] = 0;
        for (int i = 0; i < vec_len;i++){
                if(local[i]){//在回复的时候，指查看局部状态数据即可
                double ld=dist[ni][i];
                dist[ni][i] += raid;
                dist[i][ni] += raid;
                if(dist[ni][i]>0&&i<n&&ld<=0){
                    vis[i] = 0;
                    nv--;
                }
            }
        }
        vis[ni] = 0;
        return;
    }
 
    for (int i = 0; i < n;i++){
        if(!vis[i]){
            dfs(i, nv + 1);
        }
    }

    min_raid[ni] = 0;
        for (int i = 0; i < vec_len;i++){
                if(local[i]){
                double ld=dist[ni][i];
                dist[ni][i] += raid;
                dist[i][ni] += raid;
                if(dist[ni][i]>0&&i<n&&ld<=0){
                    vis[i] = 0;
                    nv--;
                }
            }
        }
    vis[ni] = 0;
}



int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);

    fcin >> n;
    fcin >> x_1 >> y_1 >> x_2 >> y_2;
    lx = min(x_1, x_2);
    rx = max(x_1, x_2);
    ly = min(y_1, y_2);
    ry = max(y_1, y_2);
    lx += 1000;
    rx += 1000;
    ly += 1000;
    ry += 1000;
    for (int i = 0; i < n;i++){
        fcin >> vetx[i][0] >> vetx[i][1];
        vetx[i][0] += 1000;
        vetx[i][1] += 1000;
    }
    vec_len = n;
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            dist[i][j] = pow(pow((vetx[i][0] - vetx[j][0]), 2) + pow((vetx[i][1] - vetx[j][1]), 2), 0.5);
        }
        dist[i][n] = abs(vetx[i][0] - lx);
        dist[i][n+1] = abs(vetx[i][0] - rx);
        dist[i][n+2] = abs(vetx[i][1] - ly);
        dist[i][n+3] = abs(vetx[i][1] - ry);
    }
   
    vis[n] = 1;
    vis[n + 1] = 1;
    vis[n + 2] = 1;
    vis[n + 3] = 1;
    for (int i = 0;i<n;i++){
        //memset(dist, 0, sizeof(dist));
        //memset(vis, 0, sizeof(vis));
        dfs(i, 1);
    }
    maxs *= M_PI;
    double S = (rx - lx) * (ry - ly);
    double ans = S - maxs;
    ans = round(ans);
    fcout << ans;

    fcin.close();
    fcout.close();

        return 0;
}