



double q_pow(double x,int p){//快速幂
    double ans = 1;
    while(p){
        if(p&1)
            ans = ans * x;
        x =  x * x;
        p>>=1;
    }
    return ans;
}

double pow(double x,int n){
    if(n==0)
        return 1;
    if(x==0)
        return 0;
    bool postive_x = x > 0 ? true : false;
    bool postive_n = n > 0 ? true : false;
    bool postive_ans = true;
    double x1;
    int n1;
    x1 = postive_x ? x : -x;
    n1 = postive_n ? n : -n;
    double ans = q_pow(x1, n1);
    if(!postive_x){
        if(n1&1)
            postive_ans = false;
        else
            postive_ans = true;
    }
    if(!postive_n)
        ans= 1 / ans;
    return postive_ans ? ans : -ans;
}

struct Listnode{
    int val;
    ListNode *next = NULL;
    ListNode(int _val) : val(_val){};
}

ListNode* reverse(ListNode* head,int n) {
    int n1 = 1;
    ListNode* pre=head;
    if(n1>=n) 
        return head;
    ListNode* p=head->next;
    n1++;
    if(n1>=n)
        return head;
    ListNode* post=p->next;
    n1++;
    while(n1<n){
        p->next=pre;
        pre = p;    
        p = post;  
        post=post->next;
    }
    head->next=NULL;
    p->next=pre;
    return p;
}

ListNode*  reverse_k(ListNode *head, int k){
    int len = 0;
    ListNode *k_next = NULL;
    ListNode *p = head;
    while(p!=NULL){
        p = p->next;
        if(len==)
        len++;
    }

}
