class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p = m - 1;
        int q = n - 1;
        int r = nums1.size() - 1;
        while (p >= 0 && q >= 0) {
            if (nums1[p] > nums2[q]) {
                nums1[r] = nums1[p];
                p--;
                r--;
            }
            else {
                nums1[r] = nums2[q];
                q--;
                r--;
            }
        }
        if (q < 0) {
            return;
        }
        else {
            while (q >= 0) {
                nums1[r] = nums2[q];
                r--;
                q--;
            }
            return;
        }
    }
};