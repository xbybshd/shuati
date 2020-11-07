/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-09-19 20:36:10
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 104
int n, m, t;

//typedef long long ll;
#define Mod 1000000007
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);
int cal[MAX];
string s1;
string s2;

int grad[4][4] = { 0 };
int a, b;
int dp[MAX][MAX][3] = { 0 };

map<char, int> mm;

int main()
{

    mm['A'] = 0;
    mm['T'] = 1;
    mm['G'] = 2;
    mm['C'] = 3;
    fcin >> s1 >> s2;
    for (int i = 0;i < 4;i++) {
        for (int j = 0;j < 4;j++) {
            fcin >> grad[i][j];
        }
    }
    fcin >> a >> b;

    int len1 = s1.length();
    int len2 = s2.length();
    int len = max(len2, len1);
    for (int i = len;i;i--) {
        dp[i][0][0] = dp[0][i][0] = dp[i][0][2] = dp[0][i][1] = 0xc0000000;
        dp[i][0][1] = dp[0][i][2] = -a - b * (i - 1);
    }
    for (int i = 1;i <= len1;i++) {
        for (int j = 1;j <= len2;j++) {
            dp[i][j][0] = max(max(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]), dp[i - 1][j - 1][2]) + grad[mm[s1[i - 1]]][mm[s2[j - 1]]];
            dp[i][j][1] = max(max(dp[i][j - 1][0] - a, dp[i][j - 1][1] - b), dp[i][j - 1][2] - a);
            dp[i][j][2] = max(max(dp[i - 1][j][0] - a, dp[i - 1][j][1] - a), dp[i - 1][j][2] - b);
        }
    }
    fcout << max(max(dp[len1][len2][0], dp[len1][len2][1]), dp[len1][len2][2]);




    fcin.close();
    fcout.close();

    return 0;
}