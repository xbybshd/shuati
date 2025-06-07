class Solution {
public:
    bool topo_dfs(std::vector<std::vector<int>>& graph, std::vector<int>& v, int x) {
        v[x] = 1;
        for (int& to : graph[x]) {
            if (v[to] == 1 || v[to] == 0 && topo_dfs(graph, v, to)) {
                return true;
            }
        }
        v[x] = 2;
        return false;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        std::vector<std::vector<int>> graph(numCourses, std::vector<int>());
        std::vector<int> v(numCourses, 0);
        for (auto& preq : prerequisites) {
            graph[preq[1]].push_back(preq[0]);
        }
        for (int i = 0; i < numCourses; i++) {
            if (v[i] == 0 && topo_dfs(graph, v, i)) {
                return false;
            }
        }
        return true;
    }
};

// BFS
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        std::vector<std::vector<int>> graph(numCourses, std::vector<int>());
        std::vector<int> v(numCourses, 0);
        for (auto& preq : prerequisites) {
            graph[preq[1]].push_back(preq[0]);
            v[preq[0]]++;
        }
        std::queue<int> que;
        int visit = 0;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == 0) {
                que.push(i);
            }
        }
        while (!que.empty()) {
            visit++;
            int node = que.front();
            que.pop();
            for (int to : graph[node]) {
                v[to]--;
                if (v[to] == 0) {
                    que.push(to);
                }
            }
        }
        return visit == numCourses;
    }
};