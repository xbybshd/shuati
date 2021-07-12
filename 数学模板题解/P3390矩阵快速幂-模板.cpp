/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
#define MAX 104

#define Mod 1000000007

using inll = unsigned long long;
inll n, m, k;
#define Mod 1000000007
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

template <typename Elem> class Matrix {
public:
    int row;
    int cow;
    Elem* mat;
    int num_size;
    int mem_size;
    Elem& get(int i, int j) {//直接返回矩阵引用可以做到下标操作的效果
        return mat[i * cow + j];
    }
    void set(int i, int j, Elem v) {
        mat[i * cow + j] = v;
    }
    Matrix(int r, int c) {
        row = r;
        cow = c;
        num_size = row * cow;
        mat = new Elem[num_size];
        mem_size = sizeof(Elem) * num_size;
        memset(mat, 0, num_size * sizeof(mat));//memset的大小，应该是元素大小乘以元素数量
    }
    void identity() {
        memset(mat, 0, num_size * sizeof(mat));
        for (int i = 0;i < min(row, cow);i++) {
            set(i, i, 1);
        }
    }
    ~Matrix() {
        delete[] mat;
    }
    Matrix(const Matrix<Elem>& b) {
        row = b.row;
        cow = b.cow;
        num_size = b.num_size;
        mem_size = b.mem_size;
        mat = new Elem[num_size];
        memcpy(mat, b.mat, mem_size);
    }

    Matrix<Elem>& operator=(const Matrix<Elem>& b) {
        row = b.row;
        cow = b.cow;
        num_size = b.num_size;
        mem_size = b.mem_size;
        delete[] mat;
        mat = new Elem[num_size];
        memcpy(mat, b.mat, mem_size);
        return *this;
    }

    Matrix<Elem> operator*(Matrix<Elem>& b) {
        Matrix<Elem> result(row, b.cow);
        for (int i = 0;i < row;i++) {
            for (int j = 0;j < b.cow;j++) {
                Elem ec = result.get(i, j);
                for (int k = 0;k < cow;k++) {
                    Elem ea = this->get(i, k);//返回引用又被赋值了，被赋值的新变量不变
                    Elem eb = b.get(k, j);
                    ec = (ec % Mod + ea % Mod * eb % Mod) % Mod;
                }
                result.set(i, j, ec);
            }
        }
        return result;
    }
};


int main()
{
    fcin >> n >> k;
    Matrix<inll> ma(n, n);
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            inll aa;
            fcin >> aa;
            ma.set(i, j, aa);
        }
    }

    Matrix<inll> mul(n, n);
    mul = ma;
    Matrix<inll> ans(n, n);
    ans.identity();//某些矩阵要设置单位矩阵
    while (k) {
        if (k & 1) {
            ans = ans * mul;
        }
        mul = mul * mul;
        k >>= 1;
    }
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            if (j != 0) fcout << " ";
            fcout << ans.get(i, j);
        }
        fcout << endl;
    }


    fcin.close();
    fcout.close();

    return 0;
}