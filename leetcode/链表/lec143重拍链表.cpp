/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* MiddleNode(ListNode* head) {
        ListNode *s, *f;
        s = f = head;
        while (f != nullptr && f->next != nullptr) {
            s = s->next;
            f = f->next->next;
        }
        return s;
    }

    ListNode* ReverseList(ListNode* head) {
        ListNode *pre = nullptr, *cur = head;
        while (cur != nullptr) {
            ListNode* temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }
    void reorderList(ListNode* head) {
        ListNode* ans = head;
        ListNode* mid = MiddleNode(head);
        ListNode* cur = ReverseList(mid);
        while (cur->next != nullptr) {
            ListNode* cnxt = cur->next;
            ListNode* hnxt = head->next;
            head->next = cur;
            cur->next = hnxt;
            head = hnxt;
            cur = cnxt;
        }
    }
};