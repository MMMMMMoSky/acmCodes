#include <cstdio>
#include <stack>
//#include <vector>
#include <algorithm>
using namespace std;

int cows, thoughts;

//tarjan信息
bool out_of_stack[10005];
int dfn[10005], low[10005];
int timenow;
stack <int> Stack;

//邻接表
int edge_num, h[10005], nx[50005], from[50005], to[50005];

//scc信息
int scc_num, belong[10005], scc_size[10005];
//vector <int> have[10005];

//scc的邻接表
//int scc_edge_cnt, scc_h[10005], scc_nx[50005], scc_to[50005];
int scc_out_degree[10005];

void addedge(int a, int b)
{
    to[++edge_num] = b;
    from[edge_num] = a;
    nx[edge_num] = h[a];
    h[a] = edge_num;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++timenow;
    Stack.push(u);
    for(int i = h[u]; i; i=nx[i])
    {
        int v = to[i];
        if(out_of_stack[v]) continue;
        if(!dfn[v]) tarjan(v);
        low[u] = min(low[u], low[v]);
    }
    if(dfn[u] == low[u])
    {
        scc_num++;
        int just_out; do {
            just_out = Stack.top();
            Stack.pop();
            scc_size[scc_num]++;
            belong[just_out] = scc_num;
            //have[scc_num].push_back(just_out);
            out_of_stack[just_out] = 1;
        }   while(just_out != u);
    }
}

int main()
{
    scanf("%d%d", &cows, &thoughts);
    for(int i = 0; i < thoughts; i++)
    {
        int a, b; 
        scanf("%d%d", &a, &b); 
        addedge(a, b);
    }

    for(int i = 1; i <= cows; i++)
    if(!out_of_stack[i]) tarjan(i);

    for(int i = 1; i <= edge_num; i++)
    {
        int u = from[i], v = to[i];
        scc_out_degree[belong[u]] += belong[u] != belong[v];
    }

    int ans_scc = 0;
    for(int i = 1; i <= scc_num; i++)
    if(!scc_out_degree[i]) {
        if(ans_scc) ans_scc = -1;
        else ans_scc = i;
    }
    if(ans_scc > 0) printf("%d\n", scc_size[ans_scc]);
    else printf("0\n");
    return 0;
}