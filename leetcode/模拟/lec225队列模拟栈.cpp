class MyStack {
public:
    std::queue<int> que;
    MyStack() {
    }

    void push(int x) {
        int n = que.size();
        que.push(x);
        for (int i = 0; i < n; i++) {
            que.push(que.front());
            que.pop();
        }
    }

    int pop() {
        int r = que.front();
        que.pop();
        return r;
    }

    int top() {
        return que.front();
    }

    bool empty() {
        return que.empty();
    }
};