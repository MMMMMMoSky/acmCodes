#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int field_num, road_num;

//邻接表
int edge_num, h[5005], nx[20005], from[20005], to[20005];

//tarjan
int timenow, dfn[5005], low[5005];

//ebc
int ebc_num, belong[5005], degree[5005];

bool visited[5005];
bool instack[5005];
bool bridge_set[20005];

void addedge(int u, int v)
{
    to[++edge_num] = v;
    from[edge_num] = u;
    nx[edge_num] = h[u];
    h[u] = edge_num;
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++timenow;
    //instack[u] = visited[u] = 1;
    visited[u] = 1;
    for(int i = h[u]; i; i=nx[i])
    {
        int v = to[i];
        if(!visited[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if(dfn[u] < low[v]) 
                bridge_set[i] = bridge_set[i&1?i+1:i-1] = 1;
        //} else if(instack[v]) {
        } else if(v != fa){
            low[u] = min(low[u], low[v]);
        }
    }
    //instack[u] = 0;
}

void dfs(int u)
{
    visited[u] = 1;
    belong[u] = ebc_num;
    for(int i = h[u]; i; i=nx[i])
    {
        int v = to[i];
        if(!visited[v] && !bridge_set[i]) dfs(v);
    }
}

int main()
{
    scanf("%d%d", &field_num, &road_num);
    for(int i = 1; i <= road_num; i++)
    {
        int a, b; scanf("%d%d", &a, &b);
        addedge(a, b);
        addedge(b, a);
    }

    //tarjan calc bridge
    for(int i = 1; i <= field_num; i++)
    if(!visited[i]) tarjan(i, 0);

    //ebc缩点
    memset(visited, 0, sizeof visited);
    for(int i = 1; i <= field_num; i++)
    if(!visited[i]) {ebc_num++; dfs(i);}

    //calc degree
    for(int i = 1; i <= edge_num; i+=2)
    if(bridge_set[i]) degree[belong[to[i]]]++, 
                      degree[belong[from[i]]]++;

    //degree == 1
    int ans = 0;
    for(int i = 1; i <= ebc_num; i++) {
        ans += degree[i] == 1;
    }
    printf("%d\n", (ans+1)>>1);
    return 0;
}