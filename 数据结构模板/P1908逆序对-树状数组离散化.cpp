#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int tree[500010],rank[500010],n;
long long ans; 
struct point
{
    int num,val;
}a[500010];
inline bool cmp(point q,point w)
{
    if(q.val==w.val)//先比较下标，再比较值
        return q.num<w.num;
    return q.val<w.val;
}
inline void insert(int p,int d)
{
    for(;p<=n;p+=p&-p)
        tree[p]+=d; 
}
inline int query(int p)
{
    int sum=0;
    for(;p;p-=p&-p)
        sum+=tree[p];
    return sum;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i].val),a[i].num=i;//输入下标
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
        rank[a[i].num]=i;//下标为x的数为第i大的数，把具体的值变成了索引的大小
    for(int i=1;i<=n;i++)
    {
        insert(rank[i],1);
        ans+=i-query(rank[i]);
    }
    printf("%lld",ans);
    return 0;
} 