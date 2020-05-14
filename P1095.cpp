#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 100000100
#define INF 0x80000000
#define MAXF 0x7fffffff
int n, m, s, t;
int sx, sy;
int u, v;

int main()
{
       ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);
    fcin >> m >> s >> t;
    int l = 0;
    int t0 = 0;
    int l2 = 0;
    int l0 = 0;
    int l1 = 0;
    while(t0<t){
        t0++;
        if(m>=10){
            m -= 10;
            l0 += 60;
            l1 = l0>(l1+17)?l0:(l1+17);
        }
        else{
            m += 4;
            l1 += 17;
        }
        
        if(l1>=s){
            fcout << "Yes\n"
                << t0;
            return 0;
        }
    }
    fcout << "No\n"
            << l1;
    


        fcin.close();
    fcout.close();

        return 0;
}