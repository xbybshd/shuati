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
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode *p1 = headA, *p2 = headB;
        int n = 0, m = 0;
        while (p1 != nullptr && p2 != nullptr) {
            p1 = p1->next;
            p2 = p2->next;
            n++;
        }
        ListNode* p3 = p1 == nullptr ? p2 : p1;
        ListNode* p4 = p1 == nullptr ? headB : headA;
        ListNode* p5 = p1 == nullptr ? headA : headB;
        while (p3 != nullptr) {
            p3 = p3->next;
            p4 = p4->next;
        }
        while (p4 != p5) {
            p4 = p4->next;
            p5 = p5->next;
        }
        return p4;
    }
};

ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    ListNode *p1 = headA, *p2 = headB;
    while (p1 != p2) {
        p1 = p1 == nullptr ? headB : p1->next;
        p2 = p2 == nullptr ? headA : p2->next;
    }
    return p1;
}