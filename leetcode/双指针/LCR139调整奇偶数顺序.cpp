class Solution {
public:
    vector<int> trainingPlan(vector<int>& actions) {
        int i0 = 0, i = 0;
        for (; i < actions.size(); i++) {
            if (actions[i] % 2 == 1) {
                // 基数就交换i0，i之后i0++，
                // 换过来的不可能是偶数，必然是奇数，所以i0一定要+1，
                // i0+1也不可能是奇书，因为i提前走一步，偶数不动，遇到奇数都已经换到前面去了，所以到最后i0一定再偶数上，等着替换
                swap(actions[i0], actions[i]);
                i0++;
            }
        }
        return actions;
    }
};