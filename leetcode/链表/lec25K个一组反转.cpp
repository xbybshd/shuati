/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-11-07 22:47:39
 */
#include <bits/stdc++.h>

using namespace std;
ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);

#include <iostream>
#include <string>
#include <utility>

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // 统计节点个数
        int n = 0;
        for (ListNode* cur = head; cur; cur = cur->next) {
            n++;
        }

        ListNode dummy(0, head);
        ListNode* p0 = &dummy;
        ListNode* pre = nullptr;
        ListNode* cur = head;

        // k 个一组处理
        for (; n >= k; n -= k) {
            for (int i = 0; i < k; i++) { // 同 92 题
                ListNode* nxt = cur->next;
                cur->next = pre; // 每次循环只修改一个 next，方便大家理解
                pre = cur;
                cur = nxt;
            }

            // 见视频
            ListNode* nxt = p0->next;
            p0->next->next = cur;
            p0->next = pre;
            p0 = nxt;
        }
        return dummy.next;
    }
};

struct ListNode {
    int val;
    ListNode* next;
    ListNode()
        : val(0)
        , next(nullptr) {}
    ListNode(int x)
        : val(x)
        , next(nullptr) {}
    ListNode(int x, ListNode* next)
        : val(x)
        , next(next) {}
};

std::pair<ListNode*, ListNode*> reverseK(ListNode* now, int k) {
    ListNode* last = now;
    for (int i = 0; i < k - 1; i++) { // 提前探明当前组是否足够k，迭代范围是k-1
        if (!last->next) { //不够就直接返回当前组开头，此时结尾是正常最后一个
            return std::pair<ListNode*, ListNode*>(now, last);
        }
        last = last->next;
    }
    ListNode* head = now;
    ListNode* p = now->next; //正常反转流程，保留下一个
    ListNode* np;
    for (int i = 0; i < k - 1; i++) {
        np = p->next; //三指针迭代
        p->next = now;
        now = p;
        p = np;
    }
    head->next = np; //将反转前的开头即反转后的结尾下一个指向下一组开头np，这里的返回在外面更新需要
    return std::pair<ListNode*, ListNode*>(now, head); //此时now也就是反转后的开头了，head不变是原开头
}

ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head || !head->next || k == 1) {
        return head;
    }
    ListNode pre(0, head);
    ListNode* group_end = &pre; //代表上一组的最后结尾，开头要用额外头节点
    ListNode* ans = nullptr;
    while (group_end->next) { //上一组的结尾默认是下一组没有反转的开头节点，如果为空就不需要继续了
        std::pair<ListNode*, ListNode*> group_range = reverseK(group_end->next, k);
        if (!ans) { //返回第一个是反转后的真正头节点，第一次迭代返回的是最后答案
            ans = group_range.first;
        }
        else { //上一组反转前的开头是上一组反转后的结尾，让上一组反转后的结尾指向这一组反转后的开头
            group_end->next = group_range.first;
        }
        group_end = group_range.second; //更新这一组反转后的结尾
    }
    return ans;
}

int main() {
    std::vector<int> a = { 1, 2, 3, 4, 5, 6, 7 };
    int k = 5;
    ListNode* pre = new ListNode;
    ListNode* head = pre;
    for (int i = 0; i < a.size(); i++) {
        ListNode* p = new ListNode(a[i]);
        pre->next = p;
        pre = p;
    }
    ListNode* ans = reverseKGroup(head->next, k);

    fcin.close();
    fcout.close();

    return 0;
}