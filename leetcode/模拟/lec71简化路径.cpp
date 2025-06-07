class Solution {
public:
    string simplifyPath(string path) {
        std::vector<std::string> node;
        istringstream ss(path);
        std::string s;
        while (std::getline(ss, s, '/')) {
            if (s.empty() || s == ".") {
                continue;
            }
            if (s != "..") {
                node.push_back(s);
            }
            else if (!node.empty()) {
                node.pop_back();
            }
        }

        std::string ans;
        for (std::string& s : node) {
            ans += "/";
            ans += s;
        }
        return node.empty() ? "/" : ans;
    }
};