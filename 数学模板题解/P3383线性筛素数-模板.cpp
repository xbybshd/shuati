#include<bits/stdc++.h>
// #include <iostream>
// #include <vector>
// #include <string>
// #include <map>
// #include <algorithm>
// #include <set>
// #include <cstring>

using namespace std;
#define MAX 5000010
#define MAXN 100000010
//int g[MAX][MAX] = {0};
#define INF 0x8f
#define MAXF 0x3f3f3f3f
bool val[MAXN];
int primer[MAX] = {0};


int main()
{


    int n, q;
    memset(val, false, sizeof(val));
    //fcin >> n >> q;
    scanf("%d%d", &n, &q);
    int cnt = 0;
    for (int i = 2; i <= n;i++){
        if(!val[i]){
            primer[cnt++] = i;
        }
        for (int j = 0; j < cnt && i * primer[j] <= n;j++){
            val[i * primer[j]] = true;
            if(i%primer[j]==0)
                break;
        }
    }
    for (int i = 0; i < q;i++){
        int qury;
        //fcin >> qury;
        scanf("%d", &qury);
        //fcout << primer[qury - 1] << "\n";
        printf("%d\n",primer[qury - 1]);
    }


   

        return 0;

}