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

using inll = unsigned long long;
#define Mod 1000000000
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);
const int max_n = 100;
int a[max_n], dp[max_n], n, m, t;
struct node {
    int high;
    int pow;
};
/*
    单调队列的本质是把内层的全部for循环变为一个单调递增的队列，每次比较只需要针对队尾即可，
    正常情况下对于一个范围内的内层比较，如果比较了比较大的，那么小的比较就可以停止，单调队列对队尾的操作
    就是每次自动把小的踢出了
*/

int main() {
    fcin >> n;
    for (int i = 1; i <= n; i++) {
        fcin >> a[i];
    }
    deque<int> que;
    fcin >> t;
    while (t--) {
        fcin >> m;
        deque<int> empty;
        swap(empty, que);
        memset(dp, 0, sizeof(dp));
        que.push_back(1);
        for (int i = 2; i <= n; i++) {
            while (!que.empty() && i - que.front() > m) { //1.队首清范围
                que.pop_front();
            }
            if (!que.empty()) { //2.机动处理根据队首得到本次的值，可以是暂时值P1776可以是最后存入的值
                if (a[que.front()] > a[i]) {
                    dp[i] = dp[que.front()];
                }
                else {
                    dp[i] = dp[que.front()] + 1;
                }
            }
            while (!que.empty() && (dp[que.back()] > dp[i] || (dp[que.back()] == dp[i] && a[que.back()] <= a[i]))) {
                que.pop_back(); //3.根据得到的值来清理队尾，具体思想是，在最开始确定是要单调递增还是单调递减队列，然后\
                根据要求将得到的值和队尾按照标准比较，单调递增的话，队尾大于得到的值就出列。\
                因为取值取得是队头，单调递增的话，队头最小，所以题意是去小的。
            }
            que.push_back(i); //清理完队头之后，再入队
        }
        fcout << dp[n] << endl;
    }

    fcin.close();
    fcout.close();

    return 0;
}