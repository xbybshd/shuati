class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        std::vector<std::vector<int>> graph(numCourses, std::vector<int>());
        std::vector<int> input_node(numCourses, 0);
        for (auto& edge : prerequisites) {
            graph[edge[1]].push_back(edge[0]);
            input_node[edge[0]]++;
        }
        std::vector<int> ans;
        std::queue<int> que;
        for (int i = 0; i < input_node.size(); i++) {
            if (input_node[i] == 0) {
                que.push(i);
            }
        }
        while (!que.empty()) {
            int u = que.front();
            ans.push_back(u);
            que.pop();
            for (int elem : graph[u]) {
                input_node[elem]--;
                if (input_node[elem] == 0) {
                    que.push(elem);
                }
            }
        }
        if (ans.size() != numCourses) {
            return std::vector<int>();
        }
        return ans;
    }
};