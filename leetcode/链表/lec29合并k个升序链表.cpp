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
    struct Compare {
        bool operator()(const ListNode* a, const ListNode* b) const {
            return a->val > b->val;
        }
    };
    std::priority_queue<ListNode*, std::vector<ListNode*>, Compare> que;
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode dummy(0, nullptr);
        ListNode* pre = &dummy;
        int seq_num = lists.size();
        for (int i = 0; i < seq_num; i++) {
            if (lists[i] != nullptr) {
                que.push(lists[i]);
            }
        }
        while (!que.empty()) {
            ListNode* u = que.top();
            pre->next = u;
            pre = pre->next;
            que.pop();
            if (u->next != nullptr) {
                que.push(u->next);
            }
        }
        return dummy.next;
    }
};