#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 5002
#define INF 0x1000000
#define MAXF 0x3f3f3f3f
int n, m, r,c;
int sx, sy;
int u, v;
int cal[MAX] = {0};
int dp[MAX] = {0};
int fan[MAX] = {0};
int alluse[10]={0};
int g[11][11];
void dfs(int ni,int *us,int gra[][11],int &numei){
    if (alluse[ni] == 0) {
        alluse[ni]=1;
        numei += 1;
    }
    us[ni]=1;
    for(int i=0;i<10;i++){
        if(us[i]==0&&gra[ni][i]==1){
            dfs(i,us,gra,numei);
        }
    }
   // us[ni]=0;
}

int mul[100];

void muli(int a){
    int inc=0;
    for(int j=0;j<99;j++){
        mul[j]=mul[j]*a+inc;
        inc=mul[j]/10;
        mul[j]%=10;
    }
}




int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);
    int pre=0;
    int use[10]={0};
    
    string num;
    int nume[32]={0};
    fcin>>num>>n;
    while(n--){
        char a,b;
        fcin>>a>>b;
        g[a-'0'][b-'0']=1;
        //g[b-'0'][a-'0']=1;
    }
    int l=num.length();
    for(int i=0;i<l;i++){
        memset(use,0,sizeof(use));
        memset(alluse,0,sizeof(alluse));
        dfs(num[i]-'0',use,g,nume[i]);
    }
    int sum=1;
    mul[0]=nume[0];
    for(int i=1;i<l;i++){
        muli(nume[i]);
    }
    int*q=mul+100;
    while(*q==0){q--;}
    int st=q-mul;
    for(int i=st;i>=0;i--){
        fcout<<mul[i];
    }
    

    fcin.close();
    fcout.close();

        return 0;
}