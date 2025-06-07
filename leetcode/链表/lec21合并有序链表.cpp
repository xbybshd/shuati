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

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode *p1, *p2, *p1_pre, *p2_pre, *p3;
    p1 = list1;
    p2 = list2;
    p1_pre = new ListNode(0, list1);
    p2_pre = new ListNode(0, list2);
    if (!p1 || !p2) {
        p3 = p1 == nullptr ? p2 : p1;
        return p3;
    }
    p3 = p1->val <= p2->val ? p1 : p2;
    while (p1 && p2) {
        while (p1 && p2 && p1->val <= p2->val) {
            p1_pre = p1;
            p1 = p1->next;
        }
        p1_pre->next = p2;
        if (!p1 || !p2) {
            break;
        }
        while (p1 && p2 && p2->val <= p1->val) {
            p2_pre = p2;
            p2 = p2->next;
        }
        p2_pre->next = p1;
    }
    if (!p1) {
        p1_pre->next = p2;
    }
    else {
        p2_pre->next = p1;
    }
    return p3;
}

int main() {
    std::vector<int> a = { -2, 5 };
    std::vector<int> b = { -9, -6, -3, -1, 1, 6 };
    int k = 5;
    ListNode* pre = new ListNode;
    ListNode* head = pre;
    for (int i = 0; i < a.size(); i++) {
        ListNode* p = new ListNode(a[i]);
        pre->next = p;
        pre = p;
    }
    ListNode* pre_b = new ListNode;
    ListNode* head_b = pre_b;
    for (int i = 0; i < b.size(); i++) {
        ListNode* p = new ListNode(b[i]);
        pre_b->next = p;
        pre_b = p;
    }
    ListNode* ans = mergeTwoLists(head->next, head_b->next);
    fcin.close();
    fcout.close();

    return 0;
}