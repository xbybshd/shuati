class Solution {
public:
    // 用图像来说，相当于一个y=x的函数，l和j分别是横坐标纵坐标，要找到一个(k,j)使得点在y=x上，初始范围是一个之分析或者矩形，
    // 初始点在最右上方，如果在小于0的时候也运行j变大
    // 猜想这样的路径，会在下一次遍历中得到。
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> ans;
        for (int i = 0; i < nums.size(); i++) {
            int j = nums.size() - 1;
            int k = i + 1;
            if (i > 0 && nums[i] == nums[i - 1]) // i先去重，从第二个开始
                continue;
            while (k < j) {
                if (k > i + 1 && nums[k] == nums[k - 1]) { //k也要去重，从第二个开始
                    k++;
                }
                else if (j < nums.size() - 1 && nums[j] == nums[j + 1]) { //j也去重，从第二个开始
                    j--;
                }
                else if (nums[i] + nums[j] + nums[k] > 0) {
                    j--;
                }
                else if (nums[i] + nums[j] + nums[k] < 0) {
                    k++;
                }
                else {
                    ans.push_back({ nums[i], nums[j], nums[k] });
                    k++;
                    j--;
                }
            }
        }
        return ans;
    }
};