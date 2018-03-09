#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

int n, m, fa[10005], d[10005];
int h[10005], nx[200005], to[200005], len[200005];
bool inq[10005], used[200005];
queue <int> Q;

void readInData()
{
    int u, v, l, e1, e2;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &l);
        e1 = i << 1, e2 = e1 | 1;
        to[e1] = v, to[e2] = u;
        nx[e1] = h[u], nx[e2] = h[v];
        h[u] = e1, h[v] = e2;
        len[e1] = len[e2] = l;
    }
}

void spfa()
{
    memset(d, (1<<7)-1, sizeof d);
    d[1] = 0;
    Q.push(1);
    int u, v, l;
    while(!Q.empty())
    {
        u = Q.front();
        Q.pop();
        inq[u] = 0;
        for(int i = h[u]; i; i = nx[i])
        {
            v = to[i], l = len[i];
            if(d[v] > d[u] + l) {
                d[v] = d[u] + l;
                fa[v] = i;
                if(!inq[v]) {
                    Q.push(v);
                    inq[v] = 1;
                }
            }
        }  
    }
}

void workout()
{
    int ans = 0;
    for(int i = 2; i <= n; i++)
    if(!used[fa[i]]) {
        ans += len[fa[i]];
        used[fa[i]|1] = 1;
        used[fa[i]-(fa[i]&1)] = 1;
    }
    printf("%d\n", ans);
}

int main()
{
    readInData();
    spfa();
    workout();
    return 0;
}