/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-10 03:41:58
 */
#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 47
#define INF 0x3f3f3f3f
#define MAXF 2010
int n, m, r, c, s;
int sx, sy;
int stacc[3][MAX] = {0};
int sq[3] = {0};
int dstin[3][MAX] = {0};
int dq[3] = {0};
char scc[3] = {'A', 'B', 'C'};
int cnt = 0;

int src[MAX] = {0};
int dsc[MAX] = {0};
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

int search_eq(int* a,int val){
    int *q = a;
    while(*q!=val){
        q++;
    }
    return q - a+1;
}

int search_big(int *a,int val){
    int *q = a;
    while(*q>val){
        q++;
    }
    return q - a;
}

void mov(int ni,int start,int end){
    sq[start]--;
    stacc[start][sq[start]] = 0;
    stacc[end][sq[end]] = ni;
    sq[end]++;
    src[ni] = end;
    fcout << "move " << ni << " from " << scc[start] << " to " << scc[end]<<"\n";
    cout << "move " << ni << " from " << scc[start] << " to " << scc[end]<<"\n";
    cnt++;
}
void hanio(int ni, int start, int mid, int end);
void clear_src(int ni,int start,int mid,int end){
    int nowni = search_eq(stacc[start], ni);
    for (int i = nowni; i < sq[start];i++){
        hanio(stacc[start][i], start, end, mid);
    }
}

void clear_dst(int ni,int start,int mid,int end){
    int nowni_big = search_big(stacc[end], ni);
    for (int i = nowni_big; i < sq[end];i++){
        hanio(stacc[end][i], end, start, mid);
    }
}

void hanio(int ni,int start,int mid,int end){
    //int nisq = src[ni];

    while(stacc[start][sq[start]-1]!=ni||(sq[end]!=0&&stacc[end][sq[end]-1]<ni)){
        if(stacc[start][sq[start]-1]!=ni)
        clear_src(ni, start, mid, end);
        if(sq[end]!=0&&stacc[end][sq[end]-1]<ni)
         clear_dst(ni, start, mid, end);
    }

    mov(ni, start, end);
}



int main()
{

    fcin >> n;
    for (int i = 0; i < 3;i++){
        fcin >> sq[i];
        if(sq[i]>0)
        for (int j = sq[i]-1; j>=0;j--){
            fcin >> stacc[i][j];
            src[stacc[i][j]] = i;
        }
        sort(stacc[i], stacc[i] + sq[i], [](int a, int b) { return a > b; });
    }
    for (int i = 0; i < 3;i++){
        fcin >> dq[i];
        if(dq[i]>0)
        for (int j = dq[i]-1; j>=0;j--){
            fcin >> dstin[i][j];
            dsc[dstin[i][j]] = i;
        }
        sort(dstin[i], dstin[i] + dq[i], [](int a, int b) { return a > b; });
    }

    for (int i = n; i > 0;i--){
        if(src[i]!=dsc[i]){
            hanio(i, src[i], 3 - src[i] - dsc[i], dsc[i]);
        }
    }
    fcout << cnt;
    fcin.close();
    fcout.close();

        return 0;
}