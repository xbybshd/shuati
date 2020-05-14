struct edge{
    int to, pre, w;
    edge(){};
};

edge emu[MAX];
int head[MAX] = {0};
void add(int u,int v,int w){
    emu[++cnt].to = v;
    emu[cnt].w = w;
    emu[cnt].pre = head[u];
    head[u] = cnt;
}