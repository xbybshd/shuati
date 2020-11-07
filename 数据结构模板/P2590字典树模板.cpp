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
#define MAXF 2003
#define P 19650827
#define M 100
int n, m, r, c, s;
int sx, sy;
//int cnt=0;
int root = 1;
int maxans = 0;
//typedef long long ll;
#define Mod 1000000007
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

int trie[MAX][26] = {0};
int cnt = 1;//总计数从1开始
int val[MAX] = {0};
//int end[MAX] = {0};是否结束单词
//int num[MAX] = {0};以节点i为前缀的单词数量

void insert(char s[]){
    int len = strlen(s);
    int p = 1;//p从1开始
    for (int i = 0; i < len;i++){
        int c = s[i] - 'a';
        if(!trie[p][c]){//此处为0
            trie[p][c] = ++cnt;//先加总计数
        }
        p = trie[p][c];//p等于当前计数点
        //num[p]++;
    }
    //end[p]=1;
}

int search(char *s){
    int len = strlen(s);
    int p = 1;
    for (int i = 0; i < len;i++){
        int c = s[i] - 'a';
        if(!trie[p][c]){
            return 0;
        }
        p = trie[p][c];
    }
    if(!val[p]){
        val[p] = 1;//判断是否重复查过
        return 1;
    }
    return 2;
}

int main()
{
    char s1[100];
    fcin >> n;
    for (int i = 1; i <= n;i++){
        scanf("%s", s1);
        insert(s1);
    }
    fcin >> m;
    for (int i = 1; i <= m;i++){
        scanf("%s", s1);
        int res = search(s1);
        if(res==0){
            printf("WRONG\n");
        }
        else if(res==1){
            printf("OK\n");
        }
        else{
            printf("REPEAT\n");
        }
    }

        fcin.close();
    fcout.close();

        return 0;
}