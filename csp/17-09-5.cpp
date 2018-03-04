#include <cstdio>
#include <algorithm>
#include <queue>
#define INVALID -1
using namespace std;

struct SegmentTree {

    #define Lchild lc,l,mid,a,b
    #define Rchild rc,mid+1,r,a,b

    int S[300005];
    queue <int> tag[300005];

    void init(int p, int l, int r)
    {
        if(l == r) {
            scanf("%d", &S[p]);
            return ;
        }
        int lc = p << 1, rc = lc | 1, mid = (l+r) >> 1;
        init(lc, l, mid);
        init(rc, mid+1, r);
        S[p] = S[lc] + S[rc];
    }

    int maintain(int p)
    {
        while(!tag[p].empty()) {
            int t = tag[p].front();
            tag[p].pop();
            if(!(S[p]%t)) S[p] /= t;
        }
        return S[p];
    }
    /*
    (gdb) n
    32                  if(!S[p]%t) S[p] /= t;
    (gdb) p S[p]%t
    $10 = 0
    (gdb) p !S[p]%t
    $11 = 0
    (gdb) p !(S[p]%t)
    $12 = true
    (gdb)
    */

    void pushdown(int p)
    {
        if(!tag[p].size()) return ;
        int lc = p << 1, rc = lc | 1;
        while(!tag[p].empty()) {
            int t = tag[p].front();
            tag[p].pop();
            tag[lc].push(t);
            tag[rc].push(t);
        }
        S[p] = INVALID;
    }

    int sum(int p, int l, int r, int a, int b)
    {
        if(l == r) return maintain(p);
        pushdown(p);
        int lc = p << 1, rc = lc | 1, mid = (l+r) >> 1;
        if(a <= l && r <= b) {
            if(S[p] != INVALID) return S[p];
            else return S[p] = sum(Lchild) + sum(Rchild);
        }
        int res = 0;
        if(a <= mid) res += sum(Lchild);
        if(b >  mid) res += sum(Rchild);
        return res;
    }

    void mark(int p, int l, int r, int a, int b, int x)
    {
        S[p] = INVALID;
        int lc = p << 1, rc = lc | 1, mid = (l+r) >> 1;
        if(a <= l && r <= b) {
            tag[p].push(x);
        } else {
            if(a <= mid) mark(Lchild, x);
            if(b >  mid) mark(Rchild, x);
        }
    }
}T;

int main()
{
    int n, m, cmd, a, b, x;
    scanf("%d%d", &n, &m);
    T.init(1, 1, n);
    for(int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &cmd, &a, &b);
        if(cmd == 1) {
            scanf("%d", &x);
            T.mark(1, 1, n, a, b, x);
        } else {
            printf("%d\n", T.sum(1, 1, n, a, b));
        }
    }
    return 0;
}