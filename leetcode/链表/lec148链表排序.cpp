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
    int getLinkLength(ListNode* head) {
        int length = 0;
        while (head) {
            length++;
            head = head->next;
        }
        return length;
    }

    // cur向前走step步，为空或者下一个为空就返回空，否则返回其下一个节点作为开始，本身下一个置空
    ListNode* splitList(ListNode* head, int size) {
        ListNode* cur = head;
        for (int i = 0; i < size - 1 && cur; i++) {
            cur = cur->next;
        }
        if (cur == nullptr || cur->next == nullptr) {
            return nullptr;
        }
        ListNode* next_head = cur->next;
        cur->next = nullptr;
        return next_head;
    }
    // 简单的二路归并链表排序
    std::pair<ListNode*, ListNode*> mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy;
        ListNode* cur = &dummy;
        while (list1 && list2) {
            if (list1->val < list2->val) {
                cur->next = list1;
                list1 = list1->next;
            }
            else {
                cur->next = list2;
                list2 = list2->next;
            }
            cur = cur->next;
        }
        cur->next = list1 ? list1 : list2;
        while (cur->next) {
            cur = cur->next;
        }
        return { dummy.next, cur };
    }
    // 先获取长度，之后按照2的指数进行for循环，每次记录当前要排序链表前一个节点和其首节点
    // 进行两部step切分，得到两个链表头指针，进行merge
    // merge返回新的头节点和尾节点，更新pre节点和pre-》next的节点即可
    ListNode* sortList(ListNode* head) {
        ListNode dummy(0, head);
        int length = getLinkLength(head);
        for (int step = 1; step < length; step *= 2) {
            ListNode* new_pre_head = &dummy;
            ListNode* cur = dummy.next;
            while (cur) {
                ListNode* head1 = cur;
                ListNode* head2 = splitList(head1, step);
                cur = splitList(head2, step);
                auto [head, tail] = mergeTwoLists(head1, head2);
                new_pre_head->next = head;
                new_pre_head = tail;
            }
        }
        return dummy.next;
    }
};