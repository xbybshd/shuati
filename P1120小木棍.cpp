#include<bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 100
#define INF 0x3f3f3f3f
#define MAXF 500020
int n, m, r, c, s;
int sx, sy;
int u, v;
int cnt = 0;
int ans = 0;
int now_len= 0;
int vec_len = 0;

int vec[66] = {0};
int lens[MAX] = {0};
int vis[66] = {0};
int nextl[66] = {0};
int maxl = 0;
int minl = INF;

int all_lens(int maxlen,int sumlen){
    int uplen = sumlen >> 1;
    int li = 0;
    for (int i = maxlen; i <= uplen;i++){
        if(sumlen%i==0){
            lens[li++] = i;
        }
    }
    lens[li] = sumlen;
    return li+1;
}

void nextvec(){
    int pre = 0;
    for (int i = 1; i <= vec_len;i++){
        if(vec[i]==vec[i-1])
            continue;
        else{
            for (int j = pre; j < i;j++){
                nextl[j] = i;
            }
            pre = i;
        }
    }
}

bool dfs(int stick_num,int last,int left_len)
{
    if(stick_num==cnt+1)
        return true;
    if(left_len==0){//如果一个木棍拼完，此部分相当于状态转移
        return dfs(stick_num + 1, 0, now_len);
    }
    if(left_len<minl)
        return false;
    int l, r, mid;
    l = last;
    r = vec_len - 1;

    while(l<r){
        mid = (l + r ) >> 1;
        if(vec[mid]<=left_len){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    for (int i = l; i < vec_len;i++){

        if(!vis[i]&&vec[i]<=left_len){
            vis[i] = 1;
            if(left_len-vec[i]>=0){//for循环的深搜，有三种情况，成功返回，失败继续下一个for,本题中如果在结尾和起始选定之后，返回失败的话\
            就没有必要继续for循环了。
                bool first_flag=dfs(stick_num, i + 1, left_len - vec[i]);
                vis[i] = 0;
                i = nextl[i] - 1;
                if(!first_flag&&(left_len==vec[i]||left_len==now_len)){
                    return false;
                }
                else if(first_flag)
                    return true;
            }
        }
    }
    return false;
}

int main()
{
   

    cin >> n;
    int sum = 0;

    int vi = 0;
    for (int i = 0; i < n;i++){
        int la;
        cin >> la;
        if(la<=50){
            vec[vi++] = la;
            sum += la;
            maxl = max(maxl, la);
            minl = min(minl, la);
        }
    }
    vec_len = vi;
    int search_num = all_lens(maxl, sum);
    sort(vec, vec + vi + 1, [](int a, int b) { return a > b; });
    nextvec();
    for (int i = 0; i < search_num;i++){
        now_len = lens[i];
        cnt = sum / now_len;
        bool all_flag = dfs(1, 0, now_len);
        memset(vis, 0, sizeof(vis));
        if(all_flag){
            cout << now_len;
            return 0;
        }
    }

        return 0;
}