class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        // 合理性，每个元素的最终位置是(i+k)%n 就是向前移动k，因为是原地转换，所以只能跳跃式的一个接一个
        // 但是如果k|n那么一圈下来，会回到原地，所以要有多个轮次
        int n = nums.size();
        k = k % n;
        int turns = gcd(k, n);
        for (int i = 0; i < turns; i++) {
            int cur = i;
            int pre = nums[i];
            do {
                int next = (cur + k) % n;
                swap(pre, nums[next]);
                cur = next;
            } while (cur != i);
        }
    }
};