class Solution {
public:
    int f(int n, int k) {
        if (n == 1) {
            return 0;
        }
        int x = f(n - 1, k);
        return (k + x) % n;
    }
    int iceBreakingGame(int num, int target) {
        return f(num, target);
    }
};

// f(n,m)代表n个元素，每次去掉第m个，最后剩余的元素，理论上来说，进行一次操作后为f(n-1,m)是n-1个元素去掉第m个后的结果
// 后面和前面的结果应该一样，可是在这里是从被去掉的点开始第二轮计数
// 在这里 序列为 k=(m-1)%n, k+1,k+2,...,k-1 是从 0,1,2,...,n-1映射而来   相当于f(n-1,m)+(k+1) = f(n-1,m)+(m-1)%n+1 = f(n-1,m)+m
// 所以 f(n,m) = (f(n-1,m)+m)%n