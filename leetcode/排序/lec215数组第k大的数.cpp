
// 小根堆解法
struct PriorQue {
    std::vector<int> que = std::vector<int>(100009, 0x3f3f3f3f);
    int idx = 0;
    void up(int p) {
        while (p > 1) {
            if (que[p] < que[p >> 1]) {
                std::swap(que[p], que[p >> 1]);
                p >>= 1;
            }
            else {
                break;
            }
        }
    };
    void down(int p) {
        int leaf = p << 1;
        while (leaf <= idx) {
            if (leaf < idx && que[leaf] > que[leaf + 1]) {
                leaf++;
            }
            if (que[p] > que[leaf]) {
                std::swap(que[p], que[leaf]);
                p = leaf;
                leaf = p << 1;
            }
            else {
                break;
            }
        }
    };
    void push(int val) {
        que[++idx] = val;
        up(idx);
    };
    void pop() {
        que[1] = que[idx--];
        down(1);
    };
    int top() {
        return que[1];
    }
};
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        PriorQue heap;
        for (int i = 0; i < nums.size(); i++) {
            if (heap.idx < k) {
                heap.push(nums[i]);
            }
            else {
                int top = heap.top();
                if (nums[i] > top) {
                    heap.pop();
                    heap.push(nums[i]);
                }
            }
        }
        return heap.top();
    }
};