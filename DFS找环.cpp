#include<iostream>
#include<cstring>
#include<cstdio>
#define maxn 500001
using namespace std;

struct  edge{
    int to,next;
    edge(){}
    edge(const int &_to,const int &_next){ to=_to,next=_next; }
}e[maxn];
int head[maxn],k;

int stack[maxn],top;
bool vis[maxn],instack[maxn],inloop[maxn];
int n,m;

inline int read(){
    register int x(0),f(1); register char c(getchar());
    while(c<'0'||'9'<c){ if(c=='-') f=-1; c=getchar(); }
    while('0'<=c&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
inline void add(const int &u,const int &v){
    e[k]=edge(v,head[u]);
    head[u]=k++;
}

void dfs(int u){
    vis[u]=instack[u]=true,stack[++top]=u;
    for(register int i=head[u];~i;i=e[i].next){
        int v=e[i].to;
        if(!vis[v]) dfs(v);
        else if(instack[v]){
            int w,t=top;
            do{
                w=stack[t--],instack[w]=false,inloop[w]=true;
            }while(w!=v);
        }
    }
    instack[u]=false,top--;
}

int main(){
    memset(head,-1,sizeof head);
    n=read(),m=read();
    for(register int i=1;i<=m;i++){
        int u=read(),v=read();
        add(u,v);
    }
    for(register int i=1;i<=n;i++) if(!vis[i]) dfs(i);
    for(register int i=1;i<=n;i++) printf("%d:%d\n",i,inloop[i]);
    return 0;
}




#include<iostream>
#include<cstring>
#include<cstdio>
#define maxn 500001
using namespace std;

struct  edge{
    int to,next;
    edge(){}
    edge(const int &_to,const int &_next){ to=_to,next=_next; }
}e[maxn<<1];
int head[maxn],k;

int dfn[maxn],fa[maxn],tot;
int n,m;

inline int read(){
    register int x(0),f(1); register char c(getchar());
    while(c<'0'||'9'<c){ if(c=='-') f=-1; c=getchar(); }
    while('0'<=c&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
inline void add(const int &u,const int &v){
    e[k]=edge(v,head[u]);
    head[u]=k++;
}

void dfs(int u){
    dfn[u]=++tot;
    for(register int i=head[u];~i;i=e[i].next){
        int v=e[i].to;
        if(v==fa[u]) continue;
        if(!dfn[v]) fa[v]=u,dfs(v);
        else if(dfn[u]<dfn[v]){
            printf("%d",v);
            do{
                printf(" %d",fa[v]),v=fa[v];
            }while(v!=u);
            puts("");
        }
    }
}

int main(){
    memset(head,-1,sizeof head);
    n=read(),m=read();
    for(register int i=1;i<=m;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    for(register int i=1;i<=n;i++) if(!dfn[i]) dfs(i);
    return 0;
}