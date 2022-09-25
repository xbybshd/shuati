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
int n, m;
int t[max_n], cnt[max_n][max_n], pre[max_n][max_n], suf[max_n][max_n], dp[max_n][max_n];
struct node {
    int l;
    int r;
    node() {};
};
node act[max_n];
/*
    易于理解的代码 https://www.luogu.com.cn/blog/longlongzhu123/ti-xie-p1973-noi2011noi-jia-nian-hua
    解释了决策单调性 和 hack数据 https://rsdbk-husky.blog.luogu.org/luogu-p1973-noi2011-noi-jia-nian-hua
    pre[i][j]=max(pre[k][j]+cnt[k][i],pre[k][j-cnt[k][i]])
*/
int main() {
    fcin >> n;
    /*
        首先需要离散化，把开头结尾所有的时间记在一个数组上，注意下标从1开始
    */
    for (int i = 1; i <= n; i++) {
        fcin >> act[i].l >> act[i].r;
        act[i].r += act[i].l;
        t[++m] = act[i].l;
        t[++m] = act[i].r;
    }
    /*
        从1开始对所有的时间节点排序，之后使用去重函数，unique返回最后一个正常值的后一个节点地址
        减去初始地址可以拿到去重后元素总长度
    */
    sort(t + 1, t + m + 1);
    m = unique(t + 1, t + m + 1) - (t + 1);
    /*
        对每个原始时间点，在去重数组中找lower_bound，得到下标减去开始节点，这里开始节点可以是0，或1，
        按照实际情况
    */
    for (int i = 1; i <= m; i++) {
        act[i].l = lower_bound(t + 1, t + 1 + m, act[i].l) - t;
        act[i].r = lower_bound(t + 1, t + 1 + m, act[i].r) - t;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = i; j <= m; j++) {
            for (int k = 1; k <= n; k++) {
                cnt[i][j] += ((i <= act[k].l) && (j >= act[k].r));
            }
        }
    }
    /*
        把dp矩阵的所有值全部置为负无穷的意义在于，我们希望所有后来的值都要从基础的dp[0][0]转移，
        有时候公式改变的值很大，但是起始值不是从00转移到的
    */
    memset(pre, 0x8f, sizeof(pre));
    memset(suf, 0x8f, sizeof(suf));
    pre[0][0] = 0;
    suf[0][0] = 0;
    int ans = 0;
    /*
        pre[i][j].当选取时间节点范围为 1-i时，其中一个组选j个活动，另外一个组要完全避开，最多选多少个
        pre[i][j]=max(pre[k][j]+cnt[k][i],pre[k][j-cnt[k][i]])  
        遍历1-i中的k
        1.在1-k中选取j个给第一组，此时pre[k][j]为第二组活动的数量，k-i时间内所有活动都给第二组，所以第二组是两个部分和
        2.1-k中选j-(k-i范围类所有活动数量)，然后k-i的活动全部给第一组，这样第二组只有前面一个部分
    */
    for (int i = 1; i <= m; i++) {
        pre[i][0] = 0;
        for (int j = 0; j <= cnt[1][i]; j++) {
            for (int k = 0; k < i; k++) {
                pre[i][j] = max(pre[i][j], pre[k][j] + cnt[k][i]);
                if (j >= cnt[k][i]) {
                    pre[i][j] = max(pre[i][j], pre[k][j - cnt[k][i]]);
                }
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = n - 1; ~j; --j) {
            pre[i][j] = max(pre[i][j], pre[i][j + 1]);
        }
    }
    for (int i = 1; i <= n; i++) {
        ans = max(ans, min(pre[m][i], i));
    }
    fcout << ans << endl;
    for (int i = m; i >= 1; i--) {
        suf[i][0] = 0;
        for (int j = 0; j <= cnt[i][m]; j++) {
            for (int k = i + 1; k <= m; k++) {
                suf[i][j] = max(suf[i][j], suf[k][j] + cnt[i][k]);
                if (j >= cnt[i][k]) { // 特判 j = 2 i = 8 k = 12
                    suf[i][j] = max(suf[i][j], suf[k][j - cnt[i][k]]);
                }
            }
        }
    }
    /*
        这一步是要完全模拟，随着j的上升单调减的情况，因为有时候不会走到这一步，还是原始最小值负无穷
        例如特判数据j = 2 i = 8 k = 12 suf[k][j] + cnt[i][k]是负无穷加一点，suf[k][j - cnt[i][k]]不会走到这里
        因为j=2，而cnt[8][12]=3,但是事实上有两个事件重合，所有可以舍弃一个重合的，cnt=2，就是可以只选取两个事件
    */
    for (int i = 1; i <= m; ++i) {
        for (int j = n - 1; ~j; --j) {
            suf[i][j] = max(suf[i][j], suf[i][j + 1]);
        }
    }
    /*
        去掉某个区间，在算小的组的最大值，对于选取区间需要每个都遍历一次
        [i][j],j>i;
        所以固定i，j区间时，对于0-i和j-m，这两个区间，我们要遍历事件总数x<cnt[0][i],y<cnt[j][m]
        正常来说x，y也要遍历，两组数据分别为
        x+y+cnt[i][j],pre[i][x]+suf[j][y];
        我们可以把cnt单独提出来，每次对两边都加上cnt，比较最小的最大值。
        假设完全反身性，x+y从开始遍历到尾部时，尾部的x+y就是开始是的pre[x]+suf[y],这样只要把cnt加到x y上
        从头到尾遍历就可以模拟加两边取最小的情况。
        反身性：有一个事实：
        当在1-i内选取j个活动时，得到另一个组的活动数pre[i][j];
        但是当在1-i内选取pre[i][j]个活动时，pre[i][pre[i][j]]=j;
    */
    for (int i = 1; i <= m; i++) {
        for (int j = i + 1; j <= m; j++) {
            dp[i][j] = -1000000;
            int y = cnt[j][m];
            for (int x = 0; x <= cnt[1][i]; x++) {
                int now, next;
                for (; y >= 0; y--) {
                    now = min(x + cnt[i][j] + y, pre[i][x] + suf[j][y]);
                    next = min(x + cnt[i][j] + y - 1, pre[i][x] + suf[j][y - 1]);
                    if (now > next) {
                        break;
                    }
                }
                dp[i][j] = max(dp[i][j], now);
            }
        }
    }
    int answer;
    for (int i = 1; i <= n; i++) {
        answer = 0;
        for (int j = 1; j <= act[i].l; j++) {
            for (int k = act[i].r; k <= m; k++) {
                answer = max(answer, dp[j][k]);
            }
        }
        fcout << answer << endl;
    }
    fcout << endl;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            fcout << cnt[i][j] << " ";
        }
        fcout << endl;
    }
    fcout << endl;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            fcout << pre[i][j] << " ";
        }
        fcout << endl;
    }
    fcout << endl;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            fcout << suf[i][j] << " ";
        }
        fcout << endl;
    }
    fcout << endl;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            fcout << dp[i][j] << " ";
        }
        fcout << endl;
    }

    fcin.close();
    fcout.close();

    return 0;
}