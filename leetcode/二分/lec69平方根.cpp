class Solution {
public:
    int mySqrt(int x) {
        int left = 0, right = std::min(x, 46340) + 1;
        while (left + 1 < right) {
            int mid = (left + right) >> 1;
            if (mid * mid <= x) {
                left = mid;
            }
            else {
                right = mid;
            }
        }
        return left;
    }
};

class Solution {
public:
    int mySqrt(int x) {
        int left = 0, right = std::min(x, 46341);
        while (left < right) { // 左闭右开，不等号
            mid = (left + right) / 2 + 1; // 这里+1是因为left等于mid的时候，如果left+1=right，如果持续进入left分支，除法结果取整数
            //mid会一直等于left无限循环，所以要跳出
            if ((long long)mid * mid <= x) { // 寻找小于traget的最大数，当小于等于时，可行解包含在左边，所以left是包含，不加1
                left = mid;
            }
            else { //大于traget的时候，mid不是可行解，right需要-1
                right = mid - 1;
            }
        }

        return left;
    }
};

// 牛顿法
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }

        double c = x, x0 = x;
        while (true) {
            double x1 = 0.5 * (x0 + c / x0);
            if (fabs(x1 - x0) < 1e-7) {
                break;
            }
            x0 = x1;
        }
        return int(x0);
    }
};
