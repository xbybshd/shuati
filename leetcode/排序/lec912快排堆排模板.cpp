// 快排关于比较条件是否带等于号会决定速度，带的话会慢，但是每次划分一定是正确的，最后的划分点的数值一定是开始选定的标记
// 左边小于等于，右边大于等于。 但是如果不带等于号，最后划分点的数值不一定是标记，所以在递归的时候，要把划分点带上，这样就不是严格的三分

// 以快排2作为标准写法

// 快排3的写法，取mid的时候，是否+1，这里不管是直接取1/2还是随机，+1的话，就是返回j [l,j],[j+1,r], 不加1返回i,[l,i-1],[i,r]
// 原理类似二分法的二分查找，(l+r)>>1配合[l,p]某些情况会陷入死循环，就是返回的p是区间右边界
void qsort(vector<int>& nums, int beg, int end) {
    if (beg >= end) {
        return;
    }
    int mid = rand() % (end - beg) + beg;
    int temp = nums[mid];
    nums[mid] = nums[beg];
    int i = beg;
    int j = end;
    while (i < j) {
        while (i < j && nums[j] >= temp)
            j--;
        nums[i] = nums[j];
        while (i < j && nums[i] <= temp)
            i++;
        nums[j] = nums[i];
    }
    nums[i] = temp;
    qsort(nums, beg, i - 1);
    qsort(nums, i + 1, end);
}
vector<int> sortArray(vector<int>& nums) {
    qsort(nums, 0, nums.size() - 1);
    return nums;
}

// 快排2
// 此种写法，最后这一点并不严格是标记，所以只能把l,i-1拿出来排，i,r拿出来排，而且这种写法必须是l,p-1否则会死循环
int partition(std::vector<int>& arr, int left, int right) {
    int pivot = arr[(left + right) / 2]; // 基准值选中间
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot)
            i++; // 从左找 >= pivot 的
        while (arr[j] > pivot)
            j--; // 从右找 <= pivot 的
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    return i; // 返回右子数组的起始位置
}

void quickSort(std::vector<int>& arr, int left, int right) {
    if (left >= right)
        return; // 递归终止条件
    int p = partition(arr, left, right); // 分区
    quickSort(arr, left, p - 1); // 排序左半部分
    quickSort(arr, p, right); // 排序右半部分
}

int partition(std::vector<int>& arr, int left, int right) {
    int pivot = arr[rand() % (right - left) + 1 + left]; // 基准值选中间
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot)
            i++; // 从左找 >= pivot 的
        while (arr[j] > pivot)
            j--; // 从右找 <= pivot 的
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    return j; // 返回右子数组的起始位置
}

void quickSort(std::vector<int>& arr, int left, int right) {
    if (left >= right)
        return; // 递归终止条件
    int p = partition(arr, left, right); // 分区
    quickSort(arr, left, p); // 排序左半部分
    quickSort(arr, p + 1, right); // 排序右半部分
}

// 快排3
int partition(std::vector<int>& nums, int l, int r) {
    // int mid = (l + r) >> 1;
    int mid = rand() % (r - l + 1) + l;
    int temp = nums[mid];
    nums[mid] = nums[l];
    while (l < r) {
        while (l < r && nums[r] >= temp) {
            r--;
        }
        nums[l] = nums[r];
        while (l < r && nums[l] <= temp) {
            l++;
        }
        nums[r] = nums[l];
    }
    nums[l] = temp;
    return l;
}
void quick_sort(std::vector<int>& nums, int l, int r) {
    if (l >= r) {
        return;
    }
    int p = partition(nums, l, r); // 分区
    quick_sort(nums, l, p - 1); // 排序左半部分
    quick_sort(nums, p + 1, r); // 排序右半部分
}

// 快排4 重复数字优化
void partition(std::vector<int>& nums, int l, int r, int& i, int& j) {
    // int mid = (l + r) >> 1;
    int mid = rand() % (r - l + 1) + l;
    int temp = nums[mid];
    nums[mid] = nums[i];
    while (i < j) {
        while (i < j && nums[j] >= temp) {
            j--;
        }
        nums[i] = nums[j];
        while (i < j && nums[i] <= temp) {
            i++;
        }
        nums[j] = nums[i];
    }
    nums[i] = temp;
    while (i > l && nums[i] == nums[i - 1])
        --i;
    while (j < r && nums[j] == nums[j + 1])
        ++j;
}
void quick_sort(std::vector<int>& nums, int l, int r) {
    if (l >= r) {
        return;
    }
    int lp = l, rp = r;
    partition(nums, l, r, lp, rp); // 分区
    quick_sort(nums, l, lp - 1); // 排序左半部分
    quick_sort(nums, rp + 1, r); // 排序右半部分
}

class Solution {
public:
    std::vector<int> prior_que = std::vector<int>(1e5 + 10, 0);
    int cnt;
    void push(int x) {
        prior_que[++cnt] = x;
        int i = cnt;
        while (i > 1 && prior_que[i] < prior_que[i >> 1]) {
            swap(prior_que[i], prior_que[i >> 1]);
            i >>= 1;
        }
    }

    void pop() {
        prior_que[1] = prior_que[cnt--];
        int i = 1;
        while (i << 1 <= cnt) {
            int left = i << 1;
            if (left < cnt && prior_que[left] > prior_que[left + 1]) {
                left++;
            }
            if (prior_que[i] > prior_que[left]) {
                swap(prior_que[left], prior_que[i]);
                i = left;
            }
            else {
                break;
            }
        }
    }

    int top() {
        return prior_que[1];
    }
    vector<int> sortArray(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            push(nums[i]);
        }
        for (int i = 0; i < nums.size(); i++) {
            nums[i] = top();
            pop();
        }
        return nums;
    }
};

// 归并排序
class Solution {
public:
    std::vector<int> tmp;
    void megre_sort(int l, int r, vector<int>& nums) {
        if (l >= r)
            return;
        int mid = l + (r - l) / 2;
        megre_sort(l, mid, nums);
        megre_sort(mid + 1, r, nums);

        int i = l, j = mid + 1, k = l;
        while (i <= mid && j <= r) {
            if (nums[i] <= nums[j]) {
                tmp[k] = nums[i];
                i++;
            }
            else {
                tmp[k] = nums[j];
                j++;
            }
            k++;
        }
        while (i <= mid) {
            tmp[k++] = nums[i++];
        }
        while (j <= r) {
            tmp[k++] = nums[j++];
        }
        copy(tmp.begin() + l, tmp.begin() + r + 1, nums.begin() + l);
    }

    vector<int> sortArray(vector<int>& nums) {
        tmp = std::move(std::vector<int>(nums.size(), 0));
        megre_sort(0, nums.size() - 1, nums);
        return nums;
    }
};