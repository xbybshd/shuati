#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 17
#define INF 0x80000000
#define MAXF 0x3f3f3f3f
int n, m, r,c;
int sx, sy;
int u, v;
int gra[MAX][MAX] = {0};
int decn[MAX][MAX][MAX]={0};
int decm[MAX][MAX][MAX] = {0};
int row[MAX] = {0};
int cow[MAX] = {0};
int drow[MAX] = {0};
int dcow[MAX][MAX] = {0};
int dp[MAX][MAX] = {0};
int mindp = MAXF;

void cal(){
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            for (int k = 0; k < m;k++){
                decn[i][j][k] += abs(gra[i][k] - gra[j][k]);
            }
        }
    }

    for (int i = 0; i < m;i++){
        for (int j = 0; j < m;j++){
            for (int k = 0; k < n;k++){
                decm[i][j][k] = abs(gra[k][i] - gra[k][j]);
            }
        }
    }
}

int dpr(){
    int pre = 0;
    for (int i = 0; i < m;i++){
        for (int j = 1; j <= c&&j<=i+1;j++){
            //int mindp = MAXF;
            if(j>1)
            for (int k = j - 2; k < i;k++){            
                 dp[i][j] =  min(dp[i][j], dp[k][j - 1] + drow[i] + dcow[i][k]);
            }
           
        }
    }
    int minedp = MAXF;
    for (int i = c - 1; i <= m;i++){
        minedp = min(minedp, dp[i][c]);
    }
    return minedp;
}


int pre(){
    int pre=-1;
    for (int i = 0; i < n;i++){
        if(row[i]==1){
            if(pre==-1){
                pre = i;
                continue;
            }
            else{
                for (int j = 0; j < m;j++){
                    drow[j] += decn[pre][i][j];
                }
                pre = i;
            }
        }
    }
    for (int i = 0; i < m;i++){
        for (int j = 0; j < m;j++){
            for (int k = 0; k < n;k++)
                if(row[k]==1)
                dcow[i][j] +=  decm[i][j][k];
            }
    }
    
}

void dfs(int ni,int ri){





    row[ni] = 1;
    if(ri==r){
        pre();
        for (int i = 0; i < m;i++){
            dp[i][1] = drow[i];
        }
        mindp = min(mindp, dpr());
       memset(dp, MAXF, sizeof(dp));
       memset(drow, 0, sizeof(drow));
       memset(dcow, 0, sizeof(dcow));
       dp[0][0] = 0;
    }
    else{       
        for (int i = ni+1; i <= n-r+ri;i++){

                dfs(i, ri + 1);
            
        }    
    }
    row[ni] = 0;

}




int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);

    fcin >> n >> m >> r >> c;
    memset(dp, MAXF, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < n;i++){
        for (int j = 0; j < m;j++){
            fcin >> gra[i][j];
        }
    }
    cal();
    for (int i = 0; i <= n-r;i++){
        row[i] = 1;
        dfs(i, 1);
        row[i] = 0;
    }
    fcout << mindp;

    fcin.close();
    fcout.close();

        return 0;
}