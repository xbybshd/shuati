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

#include <iostream>
#include <string>
#include <utility>

int lengthOfLongestSubstring(string s) {
    std::unordered_map<char, int> str_map;
    int ans = 0;
    int i = 0;
    for (int j = 0; j < s.length(); j++) {
        if (str_map.find(s[j]) != str_map.end()) {
            i = std::max(i, str_map[s[j]] + 1); // max的原因是每次更新i之后是跳步，没有把i之前全清除，所有遇到i之前重复字母就忽视i忽视i
        }
        str_map[s[j]] = j;
        ans = std::max(j - i + 1, ans);
    }
    return ans;
}

int main() {
    std::string s = "pwwkew";
    int ans = lengthOfLongestSubstring(s);

    fcin.close();
    fcout.close();

    return 0;
}