class Solution {
public:
    int uniquePaths(int m, int n) {
        std::vector<std::vector<int>> vec(m + 1, std::vector<int>(n + 1, 0));
        vec[0][1] = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vec[i + 1][j + 1] = vec[i][j + 1] + vec[i + 1][j];
            }
        }
        return vec[m][n];
    }
};

class Solution {
    long long comb(int n, int k) {
        k = min(k, n - k);
        long long res = 1;
        for (int i = 1; i <= k; i++) {
            res = res * (n + 1 - i) / i;
        }
        return res;
    }

public:
    int uniquePaths(int m, int n) {
        return comb(m + n - 2, m - 1);
    }
};
