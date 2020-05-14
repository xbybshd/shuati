#include<bits/stdc++.h>


using namespace std;



int main()
{
 

    char ssp[750];
    char ssr[750];
    int dp[750]= {0};
    int n;
    cin >> n >> ssp;
    memcpy(ssp + n, ssp, n);

    ssp[2 * n] = 0;
    int maxans = 0;
    for (int i = 0; i < 2 * n-1;i++){
        int l, r;
        l = i;
        r = i + 1;
        char lc, rc;
        lc = ssp[i];
        rc = ssp[i + 1];
        do{
            l--;
            if(ssp[l]!=lc&&lc=='w'){
                lc = ssp[l];
            }
        } while (l >= 0 && (ssp[l] == lc||ssp[l]=='w'));
        do{
            r++;
            if(ssp[r]!=rc&&rc=='w'){
                rc = ssp[r];
            }
        } while (r<=2*n-1 && (ssp[r] == rc||ssp[r]=='w'));
        dp[i] = i-l + r - i - 1;
        maxans = max(maxans, dp[i]);
    }
    if(maxans>n){
        maxans = n;
    }
    cout << maxans;


        return 0;
}