#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 1502
#define INF 0x80000000
#define MAXF 0x7fffffff
int n, m;
int sx, sy;
int u, v;
int g[MAX][MAX];

int w[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};


bool DFS(int a,int b){
    bool res=false;
    // if (g[ux][uy] == INF)
    //     return true;
    int gx = (a  / n);
    int gy = (b  / m);
    int ua = (a+ n*2000) % n;
    int ub= (b + m*2000) % m;
    if(g[ua][ub]!=INF&&g[ua][ub]!=(gx*u+gy))
        return true;
    g[(a + n) % n][(b + m) % m] = gx*u+gy;
    for (int i = 0; i < 4; i++)
    {
        int rax = a + w[i][0];
        int ux = (rax + n*2000) % n;
        int ray = b + w[i][1];
        int uy = (ray + m*2000) % m;
        int rgx = (rax  / n);
        int rgy = (ray  / m);
        if (rax>=0&&ray>=0&&rax<2000*n&&ray<2000*m&&g[ux][uy]!=MAXF)
        {   int qqqq=(rgx/u)*u+rgy%v;
            if (g[ux][uy]!=(rgx*u+rgy)||g[ux][uy] == INF)
                res=DFS(rax, ray);
            if(res)
                return res;
            // else if(g[ux][uy]!=(rgx*u+rgy)){
            //     return true;
            // }
        }
        }
        return res;
}

int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);
    u = 1000;
    v = 1000;
    int qq = INF;
    while(fcin>>n>>m){
        int a, b;
        for (int i = 0; i < n;i++)
            for (int j = 0; j < m;j++){
                char c;
                fcin >> c;
                if(c=='#')
                    g[i][j] =MAXF;
                else if(c=='.')
                    g[i][j] = INF;
                else{
                    sx= i;
                    sy = j;
                    g[i][j] = INF;
                }
            }
        bool ans;
        ans= DFS(sx+1000*n, sy+1000*m);
        fcout << (ans ? "Yes\n" : "No\n");
    }
        
    fcin.close();
    fcout.close();

        return 0;
}