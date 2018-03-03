#include <cstdio>
#include <algorithm>
using namespace std;

struct SegmentTree {

    #define Lchild lc,l,mid,a,b
    #define Rchild rc,mid+1,r,a,b

    int S[300005];
    queue <int> tag[300005];

    int maintain(int p)
    {
        while(!tag[p].empty()) {
            int t = tag[p].front();
            tag[p].pop();
            if(!S[p]%t) S[p] /= t;
        }
        return s[p];
    }

    int sum(int p, int l, int r, int a, int b)
    {
        if(l == r) return maintain(p);
        int lc = p << 1, rc = lc | 1, mid = (l+r) >> 1;
        if(l <= a && r >= b) {
            if(tag[p].empty()) return S[p];
            else {
                pushdown(p, l, r);
                return S[p] = sum(Lchild) + sum(Rchild);
            }
        }
        pushdown(p, l, r);
        int res = 0;
        if(a <= mid) res += sum(Lchild);
        if(b >  mid) res += sum(Rchild);
        return res;
    }
};