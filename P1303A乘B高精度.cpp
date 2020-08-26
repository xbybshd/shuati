#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>
// #include <cstring>

using namespace std;
#define MAX 4050
char aa[MAX];
char bb[MAX];
char cc[MAX];

int main()
{
 

     cin >> aa >> bb;
    int la = strlen(aa);
    int lb = strlen(bb);
    char *pa = aa + la - 1;
    char *pb = bb + lb - 1;
    char *pc = cc + la + lb + 3;
    for (int i = 0; i < la;i++){
        char *ec = pc - i;
        char *eb = pb;
        char *ea = pa - i;
        int inc = 0;
        for (int j = 0; j < lb;j++){
            int ens = (*ea - '0') * (*eb-- - '0') + inc;
            if(*ec!='\0')
                ens += *ec - '0';
            int d = ens % 10;
            inc = ens / 10;
            *ec-- = d+'0';
        }
        if(inc>0){
            *ec = inc + '0';
        }
    }
    char *ans = cc;
    while(*ans=='\0'){
        ans++;
    }
    if(*ans=='0')
        *(ans + 1) = '\0';
    cout << ans;


   

        return 0;

}

