#include<bits/stdc++.h>


using namespace std;
#define MAX 40009
int primer[MAX] = {0};
int phi[MAX] = {0};

int main()
{


    int n;
    cin >> n;
    if(n==1){
        cout<<"0";
        return 0;
    }
    if(n==2){
        cout << "3";
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

    cout << ans;



        return 0;
}


/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include<bits/stdc++.h>
#include <queue>
#include <map>
// #include <iostream>
// #include <cstring>

using namespace std;
#define MAX 83
#define INF 0x3f3f3f3f
#define MAXF 400
#define P 19650827
int n, m, r, c, s;
int sx, sy;
int cnt=0;
int root = 1;
int maxans = 0;
int vis[MAX] = {0};//记录每个i的最小质因子，为质数的时候为0；
int prime[MAX] = {0};//记录质数
int phi[MAX] = {0};//欧拉函数
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);

void Phi(int ni){
    for (int i = 2; i <= n;i++){
        if(vis[i]==0){
            phi[i] = i - 1;//i为质数的时候phi[i]=i-1；
            prime[++cnt] = i;//i加入质数
            vis[i] = i;//记录完之后其最小质因子为其本身
        }
        for (int j = 1; j <= cnt;j++){
            if(prime[j]>vis[i]||prime[j]*i>n)//当前选的质数不能比另一个因子的最小质因子小，当前质数乘另一个因子不能超过n
                break;
            vis[prime[j] * i] = prime[j];//其乘积的最小质因子为当前质数
            phi[prime[j] * i] = phi[i]*(i % prime[j] == 0 ? prime[j] : (prime[j] - 1));//其欧拉函数按照当前最小质因子是否整除i来分类
        }
    }
}

int main()
{
    fcin >> n;
    if(n==1){
        fcout<<"0";
        return 0;
    }
    if(n==2){
        fcout << "3";
        return 0;
    }
    Phi(n);
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