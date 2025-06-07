/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return head;
        }
        for (Node* cur = head; cur; cur = cur->next->next) {
            cur->next = new Node(cur->val, cur->next, nullptr);
        }
        for (Node* cur = head; cur; cur = cur->next->next) {
            if (cur->random) {
                cur->next->random = cur->random->next;
            }
        }
        Node* new_head = head->next;
        Node* cur = head;
        for (; cur->next->next; cur = cur->next) { // 结束条件是因为cur移动的时候，它的拷贝链表已经被摘除，但是移动到下一个还没摘除，
            //所以要考虑next->next
            Node* copy = cur->next;
            cur->next = copy->next;
            copy->next = copy->next->next;
        }
        cur->next = nullptr;
        return new_head;
    }
};