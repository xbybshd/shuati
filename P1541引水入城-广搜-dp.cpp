#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 502
#define INF 0x3f3f3f3f
#define MAXF 500020
int n, m, r, c, s;
int sx, sy;
int gra[MAX][MAX] = {0};
int visit[MAX][2] = {0};
int result[MAX][MAX] = {0};
int fdp[MAX][MAX] = {0};
int dp[MAX] = {0};
int last[MAX] = {0};

int direct[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
struct node{
    int x, y;
    node(){};
    node(int xx, int yy) : x(xx), y(yy){};
};
queue<node> que;
//node quee[250000];
int cntt = 0;
void bfs(int ni,ostream&out){
    if((ni==0&&gra[0][ni]<gra[0][ni+1])||(ni==m-1&&gra[0][ni]<gra[0][ni-1])||(gra[0][ni]<gra[0][ni+1]||gra[0][ni]<gra[0][ni-1])){
            visit[ni][0] = m;
    visit[ni][1] = -1;
    return;
    }

    que.push(node(0, ni));    
    result[0][ni] = 1;
    int l, r;
    l = m;
    r = -1;
    while(!que.empty()){
        node u = que.front();
        int ux = u.x;
        int uy = u.y;
        //cout << cntt <<" "<<ux<<" "<<uy<<" "<<que.size()<<endl;
        //cntt++;
        result[ux][uy] = 1;
        if(ux==n-1&&last[uy]==0)
            last[uy] = 1;
        if(ux==n-1){
            l = min(l, uy);
            r = max(r, uy);
        }
        que.pop();
        for (int i = 0; i < 4;i++){
            int nx = ux + direct[i][0];
            int ny = uy + direct[i][1];
            if(nx>=0&&nx<n&&ny>=0&&ny<m&&(gra[nx][ny]<gra[ux][uy])&&(result[nx][ny]==0)){
                result[nx][ny] = 1;//广搜加标签在入队列前
                    que.push(node(nx, ny));
            }
        }
    }
    visit[ni][0] = l;
    visit[ni][1] = r;
}

void dpf(){
    for (int i = 0; i < m;i++){
        dp[i] = min(dp[i], fdp[0][i]);//存在-1，-1到0，i的情况时可以提前处理0，i
        for (int j = 0; j < i;j++){
            dp[i] = min(dp[i], dp[j] + fdp[j + 1][i]);
        }
    }
}


int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);

    fcin >> n >> m;

    for (int i = 0; i < n;i++){
        for (int j = 0; j < m;j++){
            fcin >> gra[i][j];
        }
    }
    for (int i = 0; i < m;i++){
        visit[i][0] = n;
        visit[i][1] = -1;
    }

    for (int i = 0; i < m;i++){
        memset(result, 0, sizeof(result));
        bfs(i,fcout);
        //cout << i << endl;
    }
    int no = 0;
    memset(fdp, 0x3f, sizeof(fdp));
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i < m;i++){
        if(last[i]==0){
            no++;
        }
        if(!(visit[i][0]==m&&visit[i][1]==-1)){
            int l = visit[i][0];
            int r = visit[i][1];
            for (int i = l; i <= r;i++){
                fdp[l][i] = 1;
            }

        }
    }

    if (no != 0)
    {
        fcout << "0\n"
                << no << "\n";
        return 0;
    }

  //  sort(visit, visit + n + 1, [](int *a, int *b) {if(a[0]!=b[0]) return a[0]<b[0]; else return a[1]>b[1]; });
    dpf();
    fcout << "1\n"
          << dp[m - 1];

    fcin.close();
    fcout.close();

        return 0;
}