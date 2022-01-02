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
    int low;
    int high;
    int day;
    node(int l, int h, int d)
        : low(l)
        , high(h)
        , day(d) {}
};
deque<node> que;
/*
    https://www.luogu.com.cn/problem/solution/P3522
    核心思想，要判断一组范围，范围内所有的高温要大于最大的最低温，理想队列情况
    *
    * *
    * * *
    * * * *
    * * * * *
    * * * * *
      * * * *
        * * *
          * *
            *
    如果来了一个高位小于队头低位的，要把队头低位弹出
    *
    *   *
    *   * *
    *   * * *
    *   * * * *
    *   * * * *
        * * * * *
          * * * *
            * * *
              * *
                *
    如果来了一个低位高于队尾低位的，队尾低位其实没有必要存在，因为后面高位都会和最高低位比较。所以需要将其
    弹出，类似压缩的功能
    *
    *   *
    *   * *
    *   * * *
    *   * * * *
    *   * * * *   *
        * * * * * *
          * * * * *
            * * * *
              * * *
                *
    *
    *   *
    *   * *
    *   * * *
    *   * * * *
    *   * * * * *
        * * * * *
          * * * *
            * * *
              * *
    但是这种情况代表，这一轮的起始点不在刚刚进入的那一点，而在于最里面被弹出的那一点，因为直到最后一个被弹出的
    低位都比刚进入的低位低，只要和刚进位的那一点比较成功，所有的都会成功。
*/

int main() {
    fcin >> n;
    int low, high;
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        fcin >> low >> high;
        while (!que.empty() && que.front().low > high) { //
            que.pop_front();
        }
        if (!que.empty()) {
            ans = max(ans, i - que.front().day + 1);
        }
        int tmp = i; //存储最里面被弹出的那一点
        while (!que.empty() && que.back().low < low) {
            tmp = que.back().day;
            que.pop_back();
        }
        que.push_back(node(low, high, tmp));
    }
    fcout << ans;

    fcin.close();
    fcout.close();

    return 0;
}