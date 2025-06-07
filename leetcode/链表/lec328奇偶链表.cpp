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
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        ListNode *cur1 = head, *cur2 = head->next, *head2 = cur2, *pre = nullptr;
        while (cur1 != nullptr && cur1->next != nullptr) {
            cur1->next = cur2->next;
            pre = cur1;
            cur1 = cur1->next;
            if (cur1 != nullptr) {
                cur2->next = cur1->next;
                cur2 = cur2->next;
            }
        }
        if (cur1 != nullptr) {
            cur1->next = head2;
        }
        else {
            pre->next = head2;
        }
        return head;
    }
};

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
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        ListNode *cur1 = head, *cur2 = head->next, *head2 = cur2;
        while (cur2 != nullptr && cur2->next != nullptr) {
            cur1->next = cur2->next;
            cur1 = cur1->next;
            cur2->next = cur1->next;
            cur2 = cur2->next;
        }
        cur1->next = head2;
        return head;
    }
};