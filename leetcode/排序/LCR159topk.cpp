class Solution {
public:
    int topk = 0;
    int parition(std::vector<int>& nums, int l, int r) {
        int mid = (l + r) / 2;
        int guard = nums[mid];
        int i = l, j = r;
        while (i <= j) {
            while (nums[i] < guard) {
                i++;
            }
            while (nums[j] > guard) {
                j--;
            }
            if (i <= j) {
                std::swap(nums[i], nums[j]);
                i++;
                j--;
            }
        }
        return i;
    }
    void quick_sort(std::vector<int>& nums, int l, int r) {
        if (l >= r) {
            return;
        }
        int p = parition(nums, l, r);
        if (topk == p) {
            return;
        }
        else if (topk > p) {
            quick_sort(nums, p, r);
        }
        else {
            quick_sort(nums, l, p - 1);
        }
    }
    vector<int> inventoryManagement(vector<int>& stock, int cnt) {
        topk = cnt;
        quick_sort(stock, 0, stock.size() - 1);
        std::vector<int> ans(cnt, 0);
        std::copy(stock.begin(), stock.begin() + cnt, ans.begin());
        return ans;
    }
};

class Solution {
public:
    int topk = 0;
    int parition(std::vector<int>& nums, int l, int r) {
        int mid = (l + r) >> 1;
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
        int p = parition(nums, l, r);
        if (topk == p) {
            return;
        }
        else if (topk > p) {
            quick_sort(nums, p + 1, r);
        }
        else {
            quick_sort(nums, l, p - 1);
        }
    }
    vector<int> inventoryManagement(vector<int>& stock, int cnt) {
        topk = cnt;
        quick_sort(stock, 0, stock.size() - 1);
        std::vector<int> ans(cnt, 0);
        std::copy(stock.begin(), stock.begin() + cnt, ans.begin());
        return ans;
    }
};