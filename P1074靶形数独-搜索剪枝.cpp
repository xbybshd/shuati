#include <bits/stdc++>

using namespace std;



#define MAX 9
int g[MAX][MAX] = {0};
int dp[27][10] = {0};
vector<vector<int> > vl;
int n, m;
int z = 0;
const int wei[9][9] = {
{6,6,6,6,6,6,6,6,6,},
{6,7,7,7,7,7,7,7,6,},
{6,7,8,8,8,8,8,7,6,},
{6,7,8,9,9,9,8,7,6,},
{6,7,8,9,10,9,8,7,6,},
{6,7,8,9,9,9,8,7,6,},
{6,7,8,8,8,8,8,7,6,},
{6,7,7,7,7,7,7,7,6,},
{6,6,6,6,6,6,6,6,6,},
};

int max_sum = 0;

void dps(int n,int vp,int q,int sum){
    if(n==0){
        max_sum = max_sum > sum ? max_sum : sum;


        // for (int i = 0; i < 9; i++)
        // {
        //     for (int j = 0; j < 9; j++)
        // {
        //     if(j!=0){
        //         out << " ";
        //     }
        //     out << g[i][j];
        // }
        // out << endl;
        // }
        // out << endl
        //     << sum<< endl;
        return;
    }
    int p = vl[vp][0];
    int vpp = vp;
    int vq = q;
    int flag = 0;
    while(vpp<9){
        while(++vq<9){
            int aaa = g[vl[vpp][0]][vq];
            if(aaa==0){
                flag = 1;
                break;
            }
        }
        if(flag==1){
            break;
        }
        vpp++;
        vq = -1;
    }
    int c = (p / 3) * 3 + q / 3 + 18;
    for (int i = 1; i <= 9;i++){
        if(dp[p][i]==0&&dp[q+9][i]==0&&dp[c][i]==0){
            g[p][q] = i;
            dp[p][i] = 1;
            dp[q+ 9][i] = 1;
            dp[c][i] = 1;
            dps(n - 1, vpp, vq,sum+i*wei[p][q]);
            g[p][q] = 0;
            dp[p][i] = 0;
            dp[q+ 9][i] = 0;
            dp[c][i] = 0;
        }
    }
    return;
}


 



int main()
{


    for (int i = 0; i < 9;i++){
        vector<int> v1;
        v1.push_back(i);
        v1.push_back(0);
        vl.push_back(v1);
    }
    int start_sum = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int a;
            cin >> a;
            if(a!=0){
                g[i][j] = a;
                start_sum += a * wei[i][j];
                dp[i][a] = 1;
                dp[j + 9][a] = 1;
                dp[(i / 3) * 3 + j / 3+18][a] = 1;
            }
            else
            {
                vl[i][1]++;
               // vl[j+9][1]++;
                //vl[(i / 3) * 3 + j/3][1]++;
                z++;

            }
        }
    }
    sort(vl.begin(), vl.end(), [](vector<int> a, vector<int> b) { return a[1] < b[1]; });
    int sq, sp, sflag;
    sflag= sp = 0;
    sq = -1;
    while(sp<9){
        while(++sq<9){
            if(g[vl[sp][0]][sq]==0){
                sflag = 1;
                break;
            }
        }
        if(sflag==1){
            break;
        }
        sp++;
    }
    dps(z, sp, sq,start_sum);
    cout << (max_sum == 0 ? -1:max_sum);



    return 0;

}

