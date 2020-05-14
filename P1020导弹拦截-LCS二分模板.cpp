#include<bits/stdc++.h>
#include <iostream>


using namespace std;
#define MAX 20
int v[MAX]={0};
int w[MAX]={0};
int u[MAX] = {0};
int dp[MAX]={0};
int num[MAX] = {0};
int n, m;

int find_not_raise(int i,int j,int val){
    int l = i;
    int r = j;
    while(l<r){
        int mid = (l + r) >> 1;
        if(w[mid]>=val){
            l = mid+1;
        }
        else{
            r = mid;
        }
    }
    return l;
}

int find_raise(int i,int j,int val){
    int l = i;
    int r = j;
    while(l<r){
        int mid = (l + r) >> 1;
        if(u[mid]>=val){
            r=mid;
        }
        else{
            l=mid+1;
        }
    }
    return l;
}


int main()
{
    ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);

    int vi = 1;
    int wi = 1;
    int ui = 1;
    int ws = 1;
    int us = 1;
    fcin >> v[vi];
    w[wi] =v[vi];
    u[ui] = v[vi];
    vi++;
    while(fcin>>v[vi]){
        int elem = v[vi];
        wi = find_not_raise(1, ws+1, elem);
        ui = find_raise(1, us+1, elem);
        // if(wi==0)
        //     wi = 1;
        w[wi] =elem;
        u[ui] = elem;
        if(wi>ws)
            ws++;
        if(ui>us)
            us++;
        vi++;
    }
    fcout << ws << "\n"
          << us;
    fcin.close();
    fcout.close();

        return 0;

}

