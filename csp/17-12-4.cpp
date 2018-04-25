#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

int n, m, d[505];
int cnt, h[100005], nx[100005], to[100005], len[100005];
bool inq[505];
queue <int> Q;

void addedge(int u, int v, int l)
{
    cnt++;
    len[cnt] = l, to[cnt] = v;
    nx[cnt] = h[u];
    h[u] = cnt;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int t, a, b, c;
        scanf("%d%d%d%d", &t, &a, &b, &c);
        t = t ? c*c : c;
        addedge(a, b, t);
        addedge(b, a, t);
    }
    memset(d, (1<<7)-1, sizeof d);
    d[1] = 0;
    inq[1] = 1;
    Q.push(1);
    while(!Q.empty())
    {
        int now = Q.front();
        Q.pop();
        inq[now] = 0;
        for(int i = h[now]; i; i = nx[i])
        {
            int nxt = to[i], l = len[i];
            if(d[nxt] > d[now] + l) {
                d[nxt] = d[now] + l;
                if(inq[nxt]) continue;
                inq[nxt] = 1;
                Q.push(nxt);
            }
        }
    }
    printf("%d\n", d[n]);
    return 0;
}