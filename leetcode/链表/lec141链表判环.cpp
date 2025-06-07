/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode *p1, *p2;
        p1 = p2 = head;
        if (p1 == nullptr || p1->next == nullptr) {
            return false;
        }
        while (p1 != nullptr && p1->next != nullptr) {
            p1 = p1->next->next;
            p2 = p2->next;
            if (p1 == p2) {
                return true;
            }
        }
        return false;
    }
};

//环形链表找环入口
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode *s, *f;
        s = f = head;
        while (true) {
            if (f == nullptr || f->next == nullptr)
                return nullptr;
            f = f->next->next;
            s = s->next;
            if (f == s) {
                break;
            }
        }
        f = head;
        while (f != s) {
            f = f->next;
            s = s->next;
        }
        return f;
    }
};