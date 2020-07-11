class CQueue {
public:
stack<int> s1;
stack<int> s2;
    CQueue() {
    }
    
    void appendTail(int value) {
        s1.push(value);
    }
    
    int deleteHead() {//s2不空就出栈s2，空的话将s1，全部弹到s2在出栈s2
        if(s2.empty()){
            while(!s1.empty()){
                int t=s1.top();
                s1.pop();
                s2.push(t);
            }
        }
        if(s2.empty()) return -1;
        int a=s2.top();
        s2.pop();
        return a;        
    }
};