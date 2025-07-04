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