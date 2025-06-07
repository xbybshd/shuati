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
        if (head == nullptr) {
            return head;
        }
        ListNode dummy(0, head);
        ListNode *pre = &dummy, *cur = head;
        int repeat = 0;
        while (cur != nullptr) {
            // next为空说明是最后一个，不需要判断是否重复，判断当前和下一个重复仅限于倒数第二及之前的
            if (cur->next != nullptr && cur->next->val == cur->val) {
                repeat++;
            }
            // 如果存在重复，那么当走到倒数第一节点或者下一个非重复节点时，修改pre和重复标记
            else if (repeat && (cur->next == nullptr || cur->next->val != cur->val)) {
                pre->next = cur->next;
                repeat = 0;
            }
            // 其他情况就是非重复，pre随着cur动
            else {
                pre = cur;
            }
            cur = cur->next;
        }
        return dummy.next;
    }
};