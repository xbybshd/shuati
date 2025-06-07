class Node {
public:
    int key;
    int value;
    int freq = 1;
    Node* prev;
    Node* next;
    Node(int k = 0, int v = 0)
        : key(k)
        , value(v) {}
};

class LFUCache {
private:
    int min_freq;
    int capacity;
    std::unordered_map<int, Node*> key_to_node;
    std::unordered_map<int, Node*> freq_to_dummy;

    Node* get_node(int key) {
        auto it = key_to_node.find(key);
        if (it == key_to_node.end()) { // 通过key找node没找到
            return nullptr;
        }
        Node* node = it->second;
        remove(node);
        Node* dummy = freq_to_dummy[node->freq];
        if (dummy->prev == dummy) {
            freq_to_dummy.erase(node->freq);
            delete dummy;
            if (min_freq == node->freq) {
                min_freq++;
            }
        }
        push_front(++node->freq, node);
        return node;
    }

    Node* new_list() {
        Node* dummy = new Node();
        dummy->prev = dummy;
        dummy->next = dummy;
        return dummy;
    }

    void push_front(int freq, Node* x) {
        auto it = freq_to_dummy.find(freq);
        if (it == freq_to_dummy.end()) {
            it = freq_to_dummy.emplace(freq, new_list()).first;
        }
        Node* dummy = it->second;
        x->prev = dummy;
        x->next = dummy->next;
        x->prev->next = x;
        x->next->prev = x;
    }

    void remove(Node* x) {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }

public:
    LFUCache(int capacity)
        : capacity(capacity) {}

    int get(int key) {
        Node* node = get_node(key);
        return node != nullptr ? node->value : -1;
    }

    void put(int key, int value) {
        Node* node = get_node(key);
        if (node) {
            node->value = value;
            return;
        }
        if (key_to_node.size() == capacity) {
            Node* dummy = freq_to_dummy[min_freq];
            Node* back_node = dummy->prev;
            key_to_node.erase(back_node->key);
            remove(back_node);
            delete back_node;
            if (dummy->prev == dummy) {
                freq_to_dummy.erase(min_freq);
                delete dummy;
            }
        }
        key_to_node[key] = node = new Node(key, value);
        push_front(1, node);
        min_freq = 1;
    }
};

/**
     * Your LFUCache object will be instantiated and called as such:
     * LFUCache* obj = new LFUCache(capacity);
     * int param_1 = obj->get(key);
     * obj->put(key,value);
     */