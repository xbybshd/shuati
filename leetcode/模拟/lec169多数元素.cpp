class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cad = -1;
        int count = 0;
        for (int num : nums) {
            if (cad == num) {
                count++;
            }
            else if (--count < 0) {
                cad = num;
                count = 1;
            }
        }
        return cad;
    }
};