#include<bits/stdc++.h>
// #include <iostream>
// #include <vector>
// #include <string>
// #include <map>
// #include <algorithm>
// #include <set>
// #include <cstring>

using namespace std;
#define MAX 100
#define MAXN 100000010
//int g[MAX][MAX] = {0};
#define INF 0x8f
#define MAXF 0x3f3f3f3f

struct node{
    int x, y;
    node(){};
    node(int xx, int yy) : x(xx), y(yy){};
    bool operator >(const node&b){

            return y > b.y;
    }
};

node apple[5001];

int main()
{
    ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);

    int n, s, a, b;
    fcin >> n >> s >> a >> b;
    int h = a + b;
    int n1 = n;
    int cnt = 0;
    while(n1--){
        int x, y;
        fcin >> x >> y;
        if(x<=h){
            apple[cnt++] = node(x, y);
        }
    }
    //sort(apple, apple + cnt);
    for (int i = 0; i < cnt;i++)
        for (int j = 0; j < cnt - 1-i;j++){
            if(apple[j]>apple[j+1]){
                swap(apple[j], apple[j + 1]);
            }
        }
            int res = 0;
    int i;
    for (i = 0; i < cnt;i++){
        res += apple[i].y;
        if(res>s){
            break;
        }
    }
    fcout << i;

    fcin.close();
    fcout.close();

        return 0;
}