class Solution {
public:
    struct Node {
        int pos;
        int direct;
        Node(int pos_, int direct_)
            : pos(pos_)
            , direct(direct_) {};
    };
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        std::vector<Node> vec;
        for (int i = 0; i < intervals.size(); i++) {
            vec.emplace_back(Node(intervals[i][0], 1));
            vec.emplace_back(Node(intervals[i][1], -1));
        }
        std::sort(vec.begin(), vec.end(), [](const Node& a, const Node& b) {
            if (a.pos != b.pos) {
                return a.pos < b.pos;
            }
            else {
                return a.direct > b.direct;
            }
        });
        int input_num = 0;
        std::vector<std::vector<int>> ans;
        for (int i = 0; i < vec.size(); i++) {
            input_num += vec[i].direct;
            if (input_num == 1) {
                if (vec[i].direct == 1) {
                    ans.push_back(std::vector<int>());
                    ans.back().push_back(vec[i].pos);
                }
            }
            else if (input_num == 0) {
                if (vec[i].direct == -1) {
                    ans.back().push_back(vec[i].pos);
                }
            }
        }
        return ans;
    }
};

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // csort(intervals.begin(),intervals.end(),[](const std::vector<int> a,const std::vector<int>& b){
        //     return a[0]<b[0];
        // });
        std::sort(intervals.begin(), intervals.end());
        std::vector<std::vector<int>> ans;
        for (int i = 0; i < intervals.size(); i++) {
            if (!ans.empty() && intervals[i][0] <= ans.back()[1]) {
                ans.back()[1] = std::max(intervals[i][1], ans.back()[1]);
            }
            else {
                ans.emplace_back(intervals[i]);
            }
        }
        return ans;
    }
};