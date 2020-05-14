#include<bits/stdc++.h>
// #include <iostream>
// #include <vector>
// #include <string>
// #include <map>
// #include <algorithm>
// #include <set>
// #include <cstring>

using namespace std;
#define MAX 100
#define MAXN 100000010
//int g[MAX][MAX] = {0};
#define INF 0x8f
#define MAXF 0x3f3f3f3f

int primer[MAX] = {0};
int phi[MAX] = {0};
bool val[MAX];
typedef long long ll;

int main()
{
    ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);

    int n, k;
    fcin >> n >> k;
    int n1 = n;
    int n2 = n;
    int q = 0;
    int p = 0;
    int u = 0;
    int pp = 0x80000000;
    while(n1!=0){
        n1=n1 << 1;
        if((n1&0x80000000)==0x80000000){
            if(q<k) q++;
            u++;
        }
        if(q<k) p++;
    }
    if(u<=k){
        fcout << "0";
        return 0;
    }
    int nm = 1 << (32 - p - 1);
    n += nm;
    n &= 0xFFFFFFFF-(nm - 1);
    int ans = n - n2;
    fcout << ans;



    fcin.close();
    fcout.close();

        return 0;
}