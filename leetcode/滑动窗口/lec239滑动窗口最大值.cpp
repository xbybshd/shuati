class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        std::vector<int> vec;
        std::deque<int> que;
        for (int i = 0; i < nums.size(); i++) {
            while (!que.empty() && i - que.front() >= k) {
                que.pop_front();
            }
            while (!que.empty() && nums[que.back()] < nums[i]) {
                que.pop_back();
            }
            que.push_back(i);
            if (i >= k - 1)
                vec.push_back(nums[que.front()]);
        }
        return vec;
    }
};