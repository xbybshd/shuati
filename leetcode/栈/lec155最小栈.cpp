class MinStack {
public:
    std::stack<std::pair<int, int>> sp;
    MinStack() {
        sp.emplace(0, INT_MAX);
    }

    void push(int val) {
        sp.emplace(val, std::min(getMin(), val));
    }

    void pop() {
        sp.pop();
    }

    int top() {
        return sp.top().first;
    }

    int getMin() {
        return sp.top().second;
    }
};