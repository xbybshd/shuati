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
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0, head);
        ListNode *pre = &dummy, *cur = head;
        while (cur != nullptr && cur->next != nullptr) {
            ListNode* next1 = cur->next;
            ListNode* next2 = next1->next;

            cur->next = next2;
            next1->next = cur;
            pre->next = next1;
            pre = cur;
            cur = next2;
        }
        return dummy.next;
    }
};