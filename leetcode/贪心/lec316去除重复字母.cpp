class Solution {
public:
    string removeDuplicateLetters(string s) {
        std::vector<int> num(26, 0), left(26, 0);
        for (char& c : s) {
            num[c - 'a']++;
        }
        std::string ans;
        ans.reserve(s.length() + 1);
        for (char& c : s) {
            num[c - 'a']--; // 每次进入就数量减1
            if (left[c - 'a']) { // ans里面有的字符就直接略过
                continue;
            }
            // ans不空，ans末尾比当前大，而且当前不是最后一个字符，因为num是提前减的，这就规避了重复字符只保留一个的情况
            // 当前的没进入的不重复字符和没有剩下了一个的重复字符，都会进行试探踢掉ans末尾
            while (!ans.empty() && ans.back() > c && num[ans.back() - 'a']) {
                left[ans.back() - 'a'] = false;
                ans.pop_back();
            }
            ans.push_back(c);
            left[c - 'a'] = true;
        }
        return ans;
    }
};