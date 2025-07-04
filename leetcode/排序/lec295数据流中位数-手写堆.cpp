template <typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
class PriorQueue {
public:
    PriorQueue() { container.push_back(T()); };
    explicit PriorQueue(const Compare& comp_)
        : comp(comp_) {
        container.push_back(T());
    };

    void push(const T& x) {
        cnt++;
        if (cnt == container.size()) {
            container.push_back(x);
        }
        else {
            container[cnt] = x;
        }
        shift(cnt);
    }
    void pop() {
        if (!empty()) {
            container[1] = container[cnt];
            cnt--;
            down(1);
        }
    }
    bool empty() { return cnt == 0; }
    T top() {
        return container[1];
    }
    int size() { return cnt; }

private:
    Container container;
    Compare comp;
    int cnt = 0;
    void shift(int pos) {
        while (pos != 1 && comp(container[pos >> 1], container[pos])) {
            swap(container[pos], container[pos >> 1]);
            pos >>= 1;
        }
    }
    void down(int pos) {
        int limit = cnt >> 1;
        while (pos <= limit) {
            int left = pos << 1;
            if (comp(container[left], container[left + 1])) {
                left++;
            }
            if (comp(container[pos], container[left])) {
                swap(container[pos], container[left]);
                pos = left;
            }
            else {
                break;
            }
        }
    }
};

class MedianFinder {
public:
    PriorQueue<int, std::vector<int>> left_heap;
    PriorQueue<int, std::vector<int>, std::greater<int>> right_heap;
    MedianFinder() {}

    void addNum(int num) {
        if (left_heap.empty() || num <= left_heap.top()) {
            left_heap.push(num);
            if (left_heap.size() > right_heap.size() + 1) {
                right_heap.push(left_heap.top());
                left_heap.pop();
            }
        }
        else {
            right_heap.push(num);
            if (right_heap.size() > left_heap.size()) {
                left_heap.push(right_heap.top());
                right_heap.pop();
            }
        }
    }

    double findMedian() {
        if (left_heap.size() > right_heap.size()) {
            return left_heap.top();
        }
        else {
            return (left_heap.top() + right_heap.top()) / 2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */