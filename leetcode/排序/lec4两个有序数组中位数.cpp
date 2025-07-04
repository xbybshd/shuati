class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            std::swap(nums1, nums2);
        }
        int m = nums1.size(), n = nums2.size();
        int left = -1, right = m;
        while (left + 1 < right) { // left和right不合并，最后差1，因为right max是m，代表正无穷，a[i+1]，所以left只能在m之前，所以要+1隔开
            int i = (left + right) >> 1;
            int j = ((m + n + 1) >> 1) - 2 - i;
            // (m + n + 1) >> 1 代表第一组的数的数量，i代表此时a右第一组数的最右端数，则a中第一组右i+1个数，所以-i-1,
            // (m + n + 1) >> 1 -i - 1 代表此时b有多少个第一组的数，b[j]是包含其中的，但是j是索引，索引j个数，那么索引是要-1的
            if (nums1[i] <= nums2[j + 1]) {
                // 这里由单调性唯一性保证，只要找到最大的i使a[i]<=b[j+1]那么必然有a[i+1]>=b[j]
                left = i; // while中+1隔开，范围更新就不需要+1-1了，直接赋值即可
            }
            else {
                right = i;
            }
        }
        // 此时 left 等于 right-1
        // a[left] <= b[j+1] 且 a[right] > b[j'+1] = b[j]，所以答案是 i=left
        int i = left;
        int j = (m + n + 1) / 2 - 2 - i;
        int ai = i >= 0 ? nums1[i] : INT_MIN;
        int bj = j >= 0 ? nums2[j] : INT_MIN;
        int ai1 = i + 1 < m ? nums1[i + 1] : INT_MAX;
        int bj1 = j + 1 < n ? nums2[j + 1] : INT_MAX;
        int max1 = max(ai, bj);
        int min2 = min(ai1, bj1);
        return (m + n) % 2 ? max1 : (max1 + min2) / 2.0;
    }
};