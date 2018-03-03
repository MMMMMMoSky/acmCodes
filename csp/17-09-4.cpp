#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;

int n, m, N, cnt; // cnt [maybe bug]
int pre[1005], sub[1005];
int size[1005], belong[1005], dfn[1005], low[1005]; 
bool instack[1005], hasWayIn[1005], added[1005][1005];
stack <int> S;

struct AdjacencyList {
    int h[1005], nx[10005], to[10005];
    int cnt;

    AdjacencyList() {
        memset(h, 0, sizeof h);
        memset(nx, 0, sizeof nx);
        memset(to, 0, sizeof to);
        cnt = 0;
    }
    int first(int node, int &now) {
        now = h[node];
        return to[now];
    }
    int nxt(int &now) {
        now = nx[now];
        return to[now];
    }
    void addedge(int u, int v) {
        to[++cnt] = v;
        nx[cnt] = h[u];
        h[u] = cnt;
    }
}G, T;

void readInData()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G.addedge(u, v);    
    }
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    S.push(u);
    instack[u] = 1;
    int v, now;
    for(v = G.first(u, now); v; v = G.nxt(now))
    {
        if(!dfn[v]) tarjan(v);
        if(instack[v]) low[u] = min(low[u], low[v]);
    }
    if(dfn[u] == low[u]) {
        N++;
        pre[N] = sub[N] = 1;
        int t;
        do {
            t = S.top();
            S.pop();
            instack[t] = 0;
            belong[t] = N;
            size[N]++;
        }while(t != u);
    }
}

void buildT(int u)
{
    int bu = belong[u], bv;
    instack[u] = 1;
    int v, now;
    for(v = G.first(u, now); v; v = G.nxt(now))
    {
        bv = belong[v]; 
        if(!instack[v]) buildT(v);
        if(bu != bv && !added[bu][bv]) {
            T.addedge(bu, bv);
            added[bu][bv] = 1;
            hasWayIn[bv] = 1;
        }     
    }
}

void tarjanBuild()
{
    for(int i = 1; i <= n; i++)
        if(!dfn[i]) tarjan(i);    
    memset(instack, 0, sizeof instack); // used as vis[]
    for(int i = 1; i <= n; i++)
        if(!instack[i]) buildT(i);    
}

void dfs(int u)
{
    int v, now;
    for(v = T.first(u, now); v; v = T.nxt(now))
    {
        pre[v] += pre[u];
        dfs(v);
        sub[u] += sub[v]; 
    }
}

void solve()
{
    int ans = 0;
    for(int i = 1; i <= N; i++)
        if(!hasWayIn[i]) dfs(i);
    for(int i = 1; i <= N; i++) 
        if(sub[i]+pre[i] == N) ans += size[i];
    printf("%d\n", ans);
}

int main()
{
    readInData();
    tarjanBuild();
    solve();
    return 0;
}