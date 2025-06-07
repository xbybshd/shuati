/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

#include <functional>
#include <iostream>
#include <string>
#include <utility>
const int N = 1e+6 + 1;
const int M = 126;
int n, m = 128;
int x[N], y[N], cnt[N], sa[N], height[N];
// x是第一关键字，位置到排名，y是第二关键字排名到位置，cnt是字典序的排序桶，sa是最后的排名到位置

void calc_sa(std::string& s) {
    // 所有的下标从1开始，可以防止全同字符串出现的100 98 99 97 这种最后的二个无法排序的问题
    int i = 1;
    for (i = 1; i <= m; i++)
        cnt[i] = 0;
    for (i = 1; i <= n; i++)
        cnt[x[i] = s[i - 1]]++;
    for (i = 1; i <= m; i++)
        cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; i--)
        sa[cnt[x[i]]--] = i;

    for (int k = 1; k <= n; k <<= 1) {
        int p = 0; // 第二关键字排序计数
        // 前一次已经排序好了，此时用第二关键字重新安排顺序，位置最后k个后缀没有第二关键字，排到最前面
        // x是上一轮，以k为大小的子串，排序的结果，位置->排序
        for (i = n - k + 1; i <= n; i++)
            y[++p] = i;
        // 之后的排序，本质上是对位置i进行排序的时候，依据是i+k位置的部分子串排序，直接利用了上一轮的结果
        // 所以将上一轮排序结果，位置向前推k，就是当前第二关键字p顺序的位置i
        for (i = 1; i <= n; i++)
            if (sa[i] > k)
                y[++p] = sa[i] - k;

        for (i = 0; i <= m; i++)
            cnt[i] = 0;
        for (i = 1; i <= n; i++)
            cnt[x[y[i]]]++; // i是第二关键字顺序，从0开始，y[i]是第二关键字顺序i的子串的第一关键字位置，x[y[i]]是
        // 此时第一关键字在上次排序的id顺序
        for (i = 1; i <= m; i++)
            cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; i--)
            sa[cnt[x[y[i]]]--] = y[i]; // 此时i是代表第二轮排序的顺序，y[i]是第二关键字排序的第一关键字位置，x是k大小子串排序结果
        // 此时cnt的计数是按照x位置排序进行计数，最后结果是第二关键字排序为i的子串，按照第一关键字基数排序得到的顺序
        // 整体来看，是第二关键字内部先排序，如果第一关键字排序相同，第二关键字是按照之前的排好的顺序，依据就是--cnt[x[y[i]]];

        std::swap(x, y); // 当前x给y，y不要了，x更新
        p = 0;
        x[sa[0]] = 0; // x就是rk[]
        // 从一开始来说当k子串字典序完全相同的时候，sa[i]给出的i也不一样，是按照位置从后往前排的，但是rk[]不同位置字典序一样的时候。
        // 排名应该一样，所以就需要进行分别判断第一关键字和第二关键字的字典序，如果一样应该p不动
        for (i = 1; i <= n; i++) {
            x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p : ++p;
        }
        if (p == n)
            break;
        m = p; // m是这次排序产生的不同关键字个数
    }
}

void get_height(std::string& s) {
    int i, j, k = 0;
    for (i = 1; i <= n; i++) {
        if (x[i] == 1) // 这里是从顺序1开始的，1前面是没有数的
            continue;
        if (k)
            k--;
        int j = sa[x[i] - 1];
        while (s[i + k - 1] == s[j + k - 1])
            k++;
        height[x[i]] = k;
    }
}

int main() {
    std::string s;
    fcin >> s;
    n = s.length();
    calc_sa(s);
    get_height(s);
    int max_pos = 0, max_pre = 0;
    std::string ans;
    for (int i = 1; i <= n; i++) {
        if (max_pre < height[i]) {
            max_pos = sa[i];
            max_pre = height[i];
        }
    }
    for (int i = 0; i < max_pre; i++) {
        ans += s[max_pos + i - 1];
    }

    fcin.close();
    fcout.close();

    return 0;
}

// 后缀数组详解 - Ander的文章 - 知乎 https: //zhuanlan.zhihu.com/p/561024497
// https://oi-wiki.org/string/sa/#height-%E6%95%B0%E7%BB%84%E7%9A%84%E5%BA%94%E7%94%A8
// 有什么浅显易懂的后缀数组讲解 ? - README.md的回答 - 知乎
// https://www.zhihu.com/question/37401396/answer/3522274172