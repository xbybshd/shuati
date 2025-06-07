class Solution {
public:
    std::vector<int> tmp;
    int ans = 0;
    void merge_sort(int l, int r, std::vector<int>& nums) {
        if (l >= r)
            return;
        int mid = l + (r - l) / 2;
        int lt = l, rt = mid + 1, nt = mid - l + 1, k = l;
        merge_sort(l, mid, nums);
        merge_sort(mid + 1, r, nums);
        while (lt <= mid && rt <= r) {
            if (nums[lt] <= nums[rt]) {
                tmp[k] = nums[lt++];
                nt--;
            }
            else {
                tmp[k] = nums[rt++];
                ans += nt;
            }
            k++;
        }
        while (lt <= mid) {
            tmp[k++] = nums[lt++];
        }
        while (rt <= r) {
            tmp[k++] = nums[rt++];
        }
        std::copy(tmp.begin() + l, tmp.begin() + r + 1, nums.begin() + l);
    }
    int reversePairs(vector<int>& record) {
        int n = record.size();
        tmp = std::move(std::vector<int>(n, 0));
        merge_sort(0, n - 1, record);
        return ans;
    }
};