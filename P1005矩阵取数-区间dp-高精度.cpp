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
int n, m, r, c, s;
int sx, sy;
int cnt=0;
int root = 1;
int maxans = 0;
int gra[MAX][2*MAX];
ifstream fcin(".\\input.txt",ifstream::in);
ofstream fcout(".\\output.txt",ofstream::out);



struct int_b{
    int value[61] = {0};
    int l=1;
    int_b(){};
    int_b(int x){
        int xl = 1;
        while(x){
            value[xl] = x % 10;
            x /= 10;
            xl++;
        }
        xl--;
        l = !xl ? 1 : xl;
    }
    int_b(const int_b& b){
        l = b.l;
        memcpy(value, b.value, 60* sizeof(int));
    }
    int_b& operator =(const int_b& b){
        l = b.l;
        memcpy(value, b.value, 60 * sizeof(int));
    }
    int_b operator+(const int_b&b){
        int_b c;
        int addl = (l > b.l ? l : b.l)+1;
        int inc = 0;
        for (int i = 1; i <=addl;i++){
            int sum_e = value[i] + b.value[i]+inc;
            c.value[i] = sum_e % 10;
            inc = sum_e / 10;
        }
        if(c.value[addl]!=0){
            c.l = addl;
        }
        else{
            c.l = addl - 1;
        }
        return c;
    }
    int_b operator*(const int&b){
        int_b c;
        int inc = 0;
        for (int i = 1; i <= 60;i++){
            int sum_e = value[i] * b+ inc;
            c.value[i] = sum_e % 10;
            inc = sum_e / 10;
        }
        for (int i = 60; i >= 1;i--){
            if(c.value[i]!=0){
                c.l = i;
                break;
            }
        }
            return c;
    }
};

int_b dpp[MAX][MAX];
int_b base[MAX + 4];
void Base(){
    int_b ebase = int(2);
    for (int i = 2; i <= m;i++){
       ebase = ebase * 2;
       base[i] = ebase;
    }
}



int_b max_b(const int_b&a,const int_b&b){
    int al = a.l > b.l ? a.l : b.l;
    int_b c=a;
    for (int i = al; i > 0;i--){
        if(a.value[i]!=b.value[i]){
            c=a.value[i] > b.value[i]?a:b;
            return c;
        }
    }
    return c;
}

int_b dp(int ni){
    dpp[m][m] = int_b(gra[ni][m]*2);
    dpp[m + 1][m + 1] = int_b(gra[ni][m + 1]*2);
    int_b maxb;
    for (int len = 2; len <= m;len++){
        int li = m - len + 1;
        int ri = m +1;
        int rj = m + 1 + len - 1;
        for (int i = m-len+1; i <= ri;i++){
            int j = i + len - 1;
            
            int_b left = dpp[i + 1][j] +  base[len]*gra[ni][i];
            int_b right = dpp[i][j - 1] +base[len]*gra[ni][j];
            if(i==li)
                right = int_b(0);
            if(j==rj)
                left = int_b(0);
            dpp[i][j] = max_b(left,right);
            if(len==m){
                maxb = max_b(maxb, dpp[i][j]);
            }
        }
    }
    return maxb;
}


int main()
{
    fcin >> n >> m;
    int_b max_ans;
    Base();
    for (int i = 1; i <= n;i++){
        for (int j = 1; j <= m;j++){
            fcin >> gra[i][j];
            gra[i][m + j] = gra[i][j];
        }
        int_b emax = dp(i);
        memset(dpp, 0, sizeof(dpp));
        max_ans = max_ans + emax;
    }
    for (int i = max_ans.l; i >= 1;i--){
        fcout << char(max_ans.value[i] + '0');
    }

        fcin.close();
    fcout.close();

        return 0;
}