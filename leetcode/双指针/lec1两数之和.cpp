
//哈希
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashmap;
        for (int i = 0; i < nums.size(); i++) {
            int compliment = target - nums[i];
            if (hashmap.find(compliment) != hashmap.end()) {
                return { hashmap[compliment], i };
            }
            else
                hashmap[nums[i]] = i;
        }
        return {};
    }
};

//排序后双指针
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int i, j;
        i = 0;
        j = nums.size() - 1;
        std::vector<int> ans;
        std::vector<int> idx(nums.size());
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(), [&nums](int a, int b) { return nums[a] < nums[b]; });
        while (i < j) {
            int ni = idx[i];
            int nj = idx[j];
            if (nums[ni] + nums[nj] > target) {
                j--;
            }
            else if (nums[ni] + nums[nj] < target) {
                i++;
            }
            else {
                ans.push_back(ni);
                ans.push_back(nj);
                break;
            }
        }
        return ans;
    }
};