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
    ListNode* reverseList(ListNode* head) {
        ListNode* pre=head;//pre赋值给头结点
        if(pre==NULL) 
            return head;//pre为空直接返回头结点
        ListNode* p=head->next;//p赋值给头结点的下一个节点
        if(p==NULL)
            return head;//p为空直接返回头结点
        ListNode* post=p->next;//post赋值给p的下一个
        while(post!=NULL){//当post不为空
            p->next=pre;//修改p的next指向pre；
            pre = p;    //pre=p;
            p = post;   //p=post;
            post=post->next;//post前进
        }
        head->next=NULL;//改头结点的next
        p->next=pre;//改最后一个节点的next
        return p;
    }
};