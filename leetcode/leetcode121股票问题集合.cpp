
#define INF 0xBf3f3f3f

起始状态：
dp[-1][k][0] = 0;
dp[-1][k][1] = INF;//还没开始买的时候不可能持有股票，所以为负无穷



dp[i][k][0] 第i天，还可以购买k次，当天不持有股票
dp[i][k][1] 第i天，还可以购买k次，当天持有股票
dp[i][k][1]表示的是在第i天，最多进行k次交易取得的最大利润。这个最多进行k次，这样dp[i-1][k-1][0]表示的是最多进行了k-1次交易，加上一次买入\
操作，就转移到了最多进行k次交易的第i天。这个k不能认为是还剩可交易的次数，而是当时可能进行的最大交易次数。

k类似背包问题中的容量，最多选择k个物品，那么选择了k个物品的时候自然是从k-1个物品转移过来的，正常情况下，初始把k>0的全部设为-INF\
有意义的数值只能从k=0开始增加。


dp[i][k][0]=max(dp[i-1][k][0],dp[i-1][k][0]+price[i])//第i天还允许买k次，不持有股票，等于前一天不持有股票，不做动作，或者前一天\
卖了股票加上收益,的最大值，允许买股票次数都等于k的原因是，k只有前一天买了股票才会减1，卖股票不变化
dp[i][k][1]=max(dp[i-1][k][1],dp[i-1][k-1][0]-price[i])



#define MAX 100000
#define INF 0xBf3f3f3f
    int maxProfit1(vector<int>& prices) {//leetcode 121 只买卖1次，背包容量只有1
        int dp[MAX][2]={0};
        int n=prices.size();
        if(n==0) return 0;
        for(int i=0;i<n;i++){
            if(i-1==-1){
                dp[i][0]=0;
                dp[i][1]=-prices[0];
             
                continue;
            }
            dp[i][0]=max(dp[i-1][0],dp[i-1][1]+prices[i]);
           
            dp[i][1]=max(dp[i-1][1],-prices[i]);
          
        }
        return dp[n-1][0];
    }

    int maxProfit2(vector<int>& prices) {//leetcode 122可以无限次买，相当于不设容量的背包
        int dp[MAX][2]={0};
        int n=prices.size();
        if(n==0) return 0;
        for(int i=0;i<n;i++){
            if(i-1==-1){
                dp[i][0]=0;
                dp[i][1]=-prices[0];
             
                continue;
            }
            dp[i][0]=max(dp[i-1][0],dp[i-1][1]+prices[i]);
           
            dp[i][1]=max(dp[i-1][1],dp[i-1][0]-prices[i]);
          
        }
        return dp[n-1][0];
    }

class Solution {
public:
    #define MAX 100000
    #define INF 0xBf3f3f3f
    int maxProfit(vector<int>& prices) {//leetcode 123 只能买2次，要加上购买次数维度
        int dp[MAX][3][2]={0};
        int n=prices.size();
        if(n==0) return 0;
        dp[0][1][0] =0;
        dp[0][1][1] = INF;
        dp[0][2][0] = 0;
        dp[0][2][1] = INF;
        for (int i = 1; i <= n;i++){
            for (int k = 2; k >= 1;k--){
                dp[i][k][0]=max(dp[i-1][k][0],dp[i-1][k][1]+price[i-1])
                dp[i][k][1]=max(dp[i-1][k][1],dp[i-1][k-1][0]-price[i-1])
            }
        }
    }
    return dp[n][2][0];
};


class Solution {//无限次买，但是每次买有手续费
public:
    #define MAX 100000
    #define INF 0xBf3f3f3f
    int maxProfit(vector<int>& prices, int fee) {
        int dp[MAX][2]={0};
        int n=prices.size();
        if(n==0) return 0;
        for(int i=0;i<n;i++){
            if(i-1==-1){
                dp[i][0]=0;
                dp[i][1]=-prices[0]-fee;
             
                continue;
            }
            dp[i][0]=max(dp[i-1][0],dp[i-1][1]+prices[i]);
           
            dp[i][1]=max(dp[i-1][1],dp[i-1][0]-prices[i]-fee);
          
        }
        return dp[n-1][0];
    }
};