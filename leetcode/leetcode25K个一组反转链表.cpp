/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution
{
public:
    ListNode *reverse(ListNode *head, int k)
    {
        if (k == 1)
            return head;
        ListNode *cur = reverse(head->next, k - 1);
        head->next->next = head;
        head->next = NULL;
        return cur;
    }
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        int count = 0;
        ListNode *p = head;
        while (p && count < k)
        {
            count++;
            p = p->next;
        }
        if (count < k)
            return head;
        ListNode *newHead = reverse(head, k);
        head->next = reverseKGroup(p, k);
        return newHead;
    }
};
