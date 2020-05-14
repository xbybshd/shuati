#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 100
#define INF 0x80000000
#define MAXF 0x7fffffff
int n, m, s, t;
int sx, sy;
int u, v;
int qqq[MAX] = {0};

void qsort(int* beg,int *end){
    if(beg>=end)
        return;
    int* mid = (beg+(end-beg)/2);
    int temp = *mid;
    *mid = *beg;
    int *i = beg;
    int *j = end;
    while(i<j){
        while(i<j&&*j>=temp)
            j--;
        *i= *j;
        while(i<j&&*i<=temp)
            i++;
        *j = *i;

    }
    *i= temp;
    qsort(beg, i - 1);
    qsort(i + 1,end);
}

int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);
    fcin >> n;
    for (int i = 0; i < n;i++){
        fcin >> qqq[i];
    }

    qsort(qqq, qqq + n - 1);
    
    for (int i = 0; i < n;i++){
        if(i!=0)
            fcout << " ";
        fcout<< qqq[i];
    }
    fcin.close();
    fcout.close();

        return 0;
}