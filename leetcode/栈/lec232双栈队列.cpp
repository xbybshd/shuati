class MyQueue {
public:
    std::stack<int> sp1, sp2;
    MyQueue() {
    }

    void push(int x) {
        sp1.push(x);
    }

    int pop() {
        int top = this->peek();
        sp2.pop();
        return top;
    }

    int peek() {
        if (!sp2.empty())
            return sp2.top();
        if (sp1.empty())
            return -1;
        while (!sp1.empty()) {
            sp2.push(sp1.top());
            sp1.pop();
        }
        int res = sp2.top();
        return res;
    }

    bool empty() {
        return sp1.empty() && sp2.empty();
    }
};