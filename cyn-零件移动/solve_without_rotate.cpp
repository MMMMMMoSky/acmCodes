#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

#define MAXN 15
#define MAXM (1<<15)+5
#define MAX 2139062143
#define DEPO 16 //仓库
#define LOAD 17 //装配厂

int f[MAXM], fa[MAXM];

//查询x二进制右数第a位
bool bin_is(int x, int a)
{
    return bool(x&(1<<(a-1)));
}

//返回x二进制右数第a位设为b之后的值
int bin_set(int x, int a, bool b)
{
    if(b) return x | (1<<(b-1));
    else  return x & (~(1<<(b-1)));
}

//计算在y状态下, 把i从原始位置移动好需要的花费
int calc_fee(int x, int i)
{
    return 1;
}

int dp(int x)
{
    if(x == 0) return 0;
    if(f[x] < MAX) return f[x];
    for(int i = 1; i <= MAXN; i++) if(bin_is(x, i))
    {
        int y = bin_set(x, i, 0);
        int fee = calc_fee(y, i);
        if(f[x] > dp(y) + fee) {
            f[x] = f[y] + fee;
            fa[x] = y;
        }
    }
}

struct Item {
    int width, height;
    int bx, by;
    int ex, ey;
    Item(){}
    Item(int w, int h, int b1, int b2, int e1, int e2)
    {width = w, height = h, bx = b1, by = b2, ex = e1, ey = e2;}
}item[20];

// w->x h->y

void display(int x) 
{
    if(x == 0) return ;
    int t = x - fa[x];
    int which = 1;
    while(!(t&(1<<(which-1)))) which++;
    display(fa[x]);
    printf("%d\n", which);
}

int main()
{
    memset(f, (1<<7)-1, sizeof f);
    int w, h, bx, by, ex, ey;
    scanf("%d%d%d%d", &w, &h, &bx, &by);
    item[DEPO] = Item(w, h, bx, by, bx, by); // 仓库
    scanf("%d%d%d%d", &w, &h, &bx, &by);
    item[LOAD] = Item(w, h, bx, by, bx, by); // 装配厂
    for(int i = 1; i <= 15; i++)
    {
        scanf("%d%d%d%d%d%d", &w, &h, &bx, &by, &ex, &ey);
        item[i] = Item(w, h, bx, by, ex, ey);
    }
    dp((1<<MAXN)-1);
    display((1<<MAXN)-1);
    return 0;
}