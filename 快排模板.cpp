#include <bits/stdc++.h>
#include <queue>

using namespace std;
#define MAX 100
#define INF 0x80000000
#define MAXF 0x7fffffff
int n, m, s, t;
int sx, sy;
int u, v;
int qqq[MAX] = { 0 };

void qsort(int* beg, int* end) {
    if (beg >= end)
        return;
    int* mid = (beg + (end - beg) / 2);
    int temp = *mid;
    *mid = *beg;
    int* i = beg;
    int* j = end;
    while (i < j) {
        while (i < j && *j >= temp)
            j--;
        *i = *j;
        while (i < j && *i <= temp)
            i++;
        *j = *i;
    }
    *i = temp;
    qsort(beg, i - 1);
    qsort(i + 1, end);
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为基准
    int i = low - 1; // i是小于基准的元素的边界
    // [l,i]小于pivot，i+1 是pivot，（i+1,j]是大于pivot

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1; // 返回基准的最终位置
}

// 快速排序主函数
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // 获取分区点

        // 递归排序分区点前后的子数组
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    ifstream fcin(".\\input.txt", ifstream::in);
    ofstream fcout(".\\output.txt", ofstream::out);
    fcin >> n;
    for (int i = 0; i < n; i++) {
        fcin >> qqq[i];
    }

    qsort(qqq, qqq + n - 1);

    for (int i = 0; i < n; i++) {
        if (i != 0)
            fcout << " ";
        fcout << qqq[i];
    }
    fcin.close();
    fcout.close();

    return 0;
}