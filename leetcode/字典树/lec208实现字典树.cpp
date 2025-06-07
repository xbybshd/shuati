struct Node {
    Node* son[26] = {};
    int end = 0;
};
class Trie {
public:
    Node* root = new Node();
    Trie() {
    }

    int find(std::string& word) {
        Node* cur = root;
        for (char& c : word) {
            int ci = c - 'a';
            if (cur->son[ci] == nullptr) {
                return 0;
            }
            cur = cur->son[ci];
        }
        return cur->end == 1 ? 1 : 2;
    }

    void insert(string word) {
        Node* cur = root;
        for (char& c : word) {
            int ci = c - 'a';
            if (cur->son[ci] == nullptr) {
                cur->son[ci] = new Node();
            }
            cur = cur->son[ci];
        }
        cur->end = 1;
    }

    bool search(string word) {
        return find(word) == 1;
    }

    bool startsWith(string prefix) {
        return find(prefix) != 0;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */