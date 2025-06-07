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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(-500, head);
        ListNode *pre = &dummy, *cur = head;
        while (cur != nullptr) {
            while (cur != nullptr && pre->val == cur->val) {
                cur = cur->next;
            }
            pre->next = cur;
            pre = cur;
            if (cur != nullptr)
                cur = cur->next;
        }
        return head;
    }
};