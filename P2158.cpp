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

    int n;
    fcin >> n;
    if(n==1){
        fcout<<"0";
        return 0;
    }
    if(n==2){
        fcout << "3";
        return 0;
    }
    for (int i = 1; i < n;i++){
        phi[i] = i - 1;
    }
    int cnt = 0;
    for (int i = 2; i < n; i++)
    {
        if (phi[i]==i-1){
            primer[cnt++] = i;
        }
        for (int j = 0; j < cnt && i * primer[j] <= n;j++){
            phi[i * primer[j]] = phi[i] * primer[j]-(i%primer[j]==0?0:phi[i]);
            if(i%primer[j]==0)
                break;
        }
    }

    int ans = 0;
    int sum = 0;
    for (int i = 2; i < n;i++){
        sum += phi[i];
    }
    ans = 2 * sum + 3;

    fcout << ans;

    fcin.close();
    fcout.close();

        return 0;
}