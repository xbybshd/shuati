#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 5002
#define INF 0x80000000
#define MAXF 0x3f3f3f3f
int n, m, r,c;
int sx, sy;
int u, v;
int cal[MAX] = {0};
int dp[MAX] = {0};
int fan[MAX] = {0};



int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);

    fcin >> n >> m;
    int k = m;
    int sum = 0;
    for (int i = 0; i < 12;i++){
        int a = k & 1;
        sum += a*pow(n, i);
        k >>= 1;
    }
    fcout << sum;

    fcin.close();
    fcout.close();

        return 0;
}