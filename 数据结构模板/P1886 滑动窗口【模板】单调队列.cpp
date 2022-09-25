/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2021-12-25 01:36:36
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 210

#define INF 0x5000000

using ll = long long;
#define Mod 1000000000
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);
const int max_n = 500;
const int max_m = 10009;
int n, m, a[max_n];
deque<int> que_a, que_b;
int main() {
    fcin >> n >> m;
    for (int i = 1; i <= n; i++) {
        fcin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        while (!que_a.empty() && (i - que_a.front() >= m)) {
            que_a.pop_front();
        }
        while (!que_a.empty() && (a[i] < a[que_a.back()])) {
            que_a.pop_back();
        }
        que_a.push_back(i);
        if (i >= m && !que_a.empty()) {
            fcout << a[que_a.front()] << " ";
        }
    }
    fcout << endl;
    for (int i = 1; i <= n; i++) {
        while (!que_b.empty() && (i - que_b.front() >= m)) {
            que_b.pop_front();
        }
        while (!que_b.empty() && (a[i] > a[que_b.back()])) {
            que_b.pop_back();
        }
        que_b.push_back(i);
        if (i >= m && !que_b.empty()) {
            fcout << a[que_b.front()] << " ";
        }
    }

    fcin.close();
    fcout.close();

    return 0;
}