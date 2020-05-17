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
ListNode* merge(ListNode* h1,ListNode* h2){
    ListNode *p1 = h1;
    ListNode *p2 = h2;
    ListNode *head = new ListNode(0);
    ListNode *p3 = head;
    while(p1!=nullptr&&p2!=nullptr){
        if(p1->val<p2->val){
            p3->next = p1;
            p1 = p1->next;
        }
        else{
            p3->next = p2;
            p2 = p2->next;
        }
        p3 = p3->next;
    }
    p3->next = p2? p2 : p1;
    ListNode *ans = head->next;
    delete head;
    return ans;
}


ListNode* sortList(ListNode* head) {
    if (head == NULL || head->next == NULL){
        return head;
    }
    ListNode *front = head;
    ListNode *pre_fornt=nullptr;
    ListNode *rear = head;
    while(rear!=nullptr&&rear->next!=nullptr){//两个只要有一个为空就停下来
        pre_fornt=front;
        front = front->next;
        rear = rear->next->next;
    }
    pre_fornt->next=nullptr;
    return merge(sortList(head), sortList(front));//head----pre_front
    }
};