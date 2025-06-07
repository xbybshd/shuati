class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int min_pos = 0, min_gas = 0, total = 0; // mingas=0因为如果是0位置最小即开始是正的而且后续sum都大于0，就是从0开始,此时不需要进if
        int n = gas.size();
        for (int i = 0; i < n; i++) {
            total += gas[i] - cost[i];
            if (total < min_gas) {
                min_gas = total;
                min_pos = i + 1;
            }
        }
        return total < 0 ? -1 : min_pos;
    }
};