#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int n, m; //货币种类, 兑换点个数
int s; //初始货币种类
double numS; //s的数量
double maxd[105]; //最长路

int cnt, h[105], nx[205], to[205]; //邻接表
double rate[205], cms[205]; //汇率和中转费

queue <int> q; //spfa队列
bool inq[105]; 
int viscnt[105]; //入队次数

void addedge(int u, int v, double r, double c)
{
    to[++cnt] = v;
    cms[cnt] = c;
    rate[cnt] = r;
    nx[cnt] = h[u]; 
    h[u] = cnt;
}

bool spfa() //有正环返回1
{
    maxd[s] = numS;
    q.push(s);
    inq[s] = 1;
    viscnt[s]++;
    while(!q.empty()) {
        int t = q.front();
        q.pop();
        inq[t] = 0;
        for(int i = h[t]; i; i = nx[i]) {
            double change = (maxd[t]-cms[i])*rate[i]; //转手之后
            if(change > maxd[to[i]]) {
                maxd[to[i]] = change;
                if(!inq[to[i]]) {  //注意, 是入队n次, 而不是被更新n次
                    viscnt[to[i]]++;
                    if(viscnt[to[i]] == n) return 1;
                    inq[to[i]] = 1;
                    q.push(to[i]);
                }
            }
        }
    }
    return 0;
}

int main()
{
    scanf("%d%d%d%lf", &n, &m, &s, &numS);
    for(int i = 1; i <= m; i++)
    {
        int a, b;
        double r, c;
        scanf("%d%d", &a, &b);
        scanf("%lf%lf", &r, &c);
        addedge(a, b, r, c);
        scanf("%lf%lf", &r, &c);
        addedge(b, a, r, c);
    }

    printf(spfa()?"YES":"NO");
    return 0;
}