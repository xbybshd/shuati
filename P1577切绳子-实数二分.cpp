/*
 * @Author: xbybshd 
 * @Date: 2020-03-09 18:06:40 
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-12 00:32:11
 */
#include<bits/stdc++.h>
// #include <queue>
// #include <map>

using namespace std;
#define MAX 10000
#define INF 0x3f3f3f3f
#define MAXF 2010
int n, m, r, c, s;
int sx, sy;
double cal[MAX];

ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);


int max_t(int a,int b,int c){
    int x = a > b ? a : b;
    int y = x > c ? x : c;
    return y;
};

bool judge(double ni){
    int nume = 0;
    for (int i = 0; i < n;i++){
        nume += int(cal[i] / ni);
    }
    if(nume>=m)
        return true;
    else
        return false;
}
int main()
{

    fcin >> n >> m;
    double sum = 0;
    for (int i = 0; i < n;i++){
        fcin >> cal[i];
        sum += cal[i];
    }
    double r = sum / m;
    double l = 0.01;
    while(l+1e-4<r){
        double mid = (l + r) / 2;
        if(judge(mid))
            l = mid;
        else
            r = mid;
    }
    fcout.setf(ios::fixed,ios::floatfield);
    r =double((int(r * 100))) / 100;
    fcout << setprecision(2) << r;

    fcin.close();
    fcout.close();

        return 0;
}