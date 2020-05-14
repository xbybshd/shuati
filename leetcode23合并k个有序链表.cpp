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
struct node{
    int val;
    int ni;
    node(int _val,int _ni):val(_val),ni(_ni){};
    bool operator<(const node& b)const{//重载运算符最好带const
        return val>b.val;//小顶堆，小于号反过来
    }
};
priority_queue<node> que;
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int len=lists.size();
        ListNode *p=new ListNode(0);//解决头结点的方法
        ListNode* head=p;
        bool first=true;
        for(int i=0;i<len;i++){
            if(lists[i]!=NULL){
                que.push(node(lists[i]->val,i));
            }
        }
        while(!que.empty()){
            int min_i=que.top().val;
            int min_v=que.top().ni;
            que.pop();
            p->next=new ListNode(min_i);
            p=p->next;
            lists[min_v]=lists[min_v]->next;
            if(lists[min_v]!=NULL)
                que.push(node(lists[min_v]->val,min_v));
            
        }
        return head->next;
    }
};