/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include<bits/stdc++.h>
#include <queue>
#include <map>
#include <string>
// #include <iostream>
// #include <cstring>

using namespace std;
#define MAX 5009
#define INF 0x3f3f3f3f
#define MAXF 12000
#define P 19650827
// int n, m, r, c, s;
// int sx, sy;
// int cnt=0;
// int root = 1;
// int maxans = 0;
typedef unsigned long long ull;
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

int vis[10]={0};
char cs[10];
int vcs[10][10]={0};
char emu[10];
char uemu[10];
vector<string> ans;
int simler[10]={0};
int l=0;
void dfs(int ni,int ns){
    cs[ns]=emu[ni];
    if(ns==l){
        cs[ns+1]=0;
        string es(cs+1);
        ans.push_back(es);
        return;
    }
    for(int i=1;i<=l;i++){
        if(!vis[i]){
            vis[i]=1;
            if(!vcs[ns+1][simler[i]]){//如果下一个位置上，第simler[i]个字符没有被使用就递归
                vcs[ns+1][simler[i]]=1;//相同的字符的simler[i]是一样的，使用此位置出现一次某字符之后，就不应该出现其他相同的字符
                dfs(i,ns+1);
            }
            vis[i]=0;
        }
    }
    memset(vcs[ns+1],0,sizeof(vcs[ns+1]));//下一位置的字符使用情况应该在所有遍历结束之后再清理
}

int ff[MAX*4] = {0};
int main()
{
    string s;
    fcin >> s;
    sort(s.begin(), s.end());
    l=s.length();
    emu[1]=uemu[1]=s[0];
    simler[1]=1;
    for(int i=1;i<l;i++){
        emu[i+1]=s[i];
        if(emu[i+1]!=emu[i]){
            uemu[i+1]=s[i];
            simler[i+1]=i+1;
        }
        else{
            simler[i+1]=simler[i];
        }
    }
    for(int i=1;i<=l;i++){
        vis[i]=1;
        if(!vcs[1][simler[i]]){
            vcs[1][simler[i]]=1;//遍历去重，将相同的字符位置映射到这个字符第一次出现的位置
            dfs(i,1);
        }
        vis[i]=0;
    }
    vector<string> res=ans;

   

    fcin.close();
    fcout.close();

        return 0;
}