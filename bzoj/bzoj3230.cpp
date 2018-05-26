#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define SZ 100005
using namespace std;
 
int n, q, s1[SZ], s2[SZ];
int sa1[SZ], r1[SZ], h1[SZ], rmq1[SZ][18];
int sa2[SZ], r2[SZ], h2[SZ], rmq2[SZ][18];
long long sum[SZ];
 
void Read ()
{
    scanf ("%d %d", &n, &q);
    char c = getchar();
    while (c < 'a' || c > 'z') c = getchar();
    for (int i = 1; i <= n; i++)
    {
        s1[i-1] = s2[n-i] = c-'a'+1;
        c = getchar();
    }
}
 
int cmp (int *s, int i, int j, int l)
{return s[i]==s[j] && s[i+l]==s[j+l];}
 
void buildsa (int *s, int *sa, int *rank, int *height, int m) 
{
    n++;
    int a[SZ], b[SZ], c[SZ], d[SZ];
    int i, j, p, k = 0, *x = a, *y = b, *t;
    for (i = 0; i < m; i++) c[i] = 0;
    for (i = 0; i < n; i++) c[x[i]=s[i]]++;
    for (i = 1; i < m; i++) c[i] += c[i-1];
    for (i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;    
 
    for (j = p = 1; p < n; j<<=1, m=p)
    {
        for (p = 0, i = n-j; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++) 
            if (sa[i] >= j) y[p++] = sa[i]-j;
        for (i = 0; i < n; i++) d[i] = x[y[i]];
        for (i = 0; i < m; i++) c[i] = 0;
        for (i = 0; i < n; i++) c[d[i]]++;
        for (i = 1; i < m; i++) c[i] += c[i-1];
        for (i = n-1; i >= 0; i--) sa[--c[d[i]]] = y[i];
         
        for (t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1; i < n; i++)
        x[sa[i]] = cmp(y,sa[i-1],sa[i],j) ? p-1 : p++;
    }
 
    n--;
    for (i = 1; i <= n; i++) rank[sa[i]] = i;
    for (i = 0; i <  n; height[rank[i++]] = k)
    for (k?k--:0, j=sa[rank[i]-1]; s[i+k]==s[j+k]; k++);
}
 
void BuildSa ()
{
    buildsa(s1,sa1,r1,h1,27);
    buildsa(s2,sa2,r2,h2,27);
    sum[1] = n-sa1[1];
    for (int i = 2; i <= n; i++)
        sum[i] = sum[i-1]+(long long)(n-sa1[i]-h1[i]);
}
 
void BuildRmq ()
{
    for (int i = 1; i <= n; i++)
        rmq1[i][0] = h1[i], rmq2[i][0] = h2[i];
    for (int i = 1; (1<<i) <= n; i++)
    for (int j = 1; j+(1<<i)-1 <= n; j++)
        rmq1[j][i] = min(rmq1[j][i-1],rmq1[j+(1<<i-1)][i-1]),
        rmq2[j][i] = min(rmq2[j][i-1],rmq2[j+(1<<i-1)][i-1]);
}
 
void Query (long long k, int &lk, int &rk)
{
    if (sum[n] < k) {lk = -1; return;}
    int l = 1, r = n, mid;
    while (l < r)
    {
        mid = (l+r)/2;
        if (sum[mid] >= k) r = mid;
        else l = mid + 1;
    }
    lk = sa1[l];
    rk = sa1[l]+k+h1[l]-(l?sum[l-1]:0)-1;
}
 
int lcp (int l, int r, bool flag)
{
    if (l == r) return 9999999;
    if (flag)
    {
        l = r1[l], r= r1[r];
        if (l > r) swap(l,r);
        int k = 0; l++;
        if (l == r) return rmq1[l][0];
        while ((1<<k+1) <= r-l+1) k++;
        return min(rmq1[l][k],rmq1[r-(1<<k)+1][k]);
    }
    else
    {
        l = r2[l], r= r2[r];
        if (l > r) swap(l,r);
        int k = 0; l++;
        if (l == r) return rmq2[l][0];
        while ((1<<k+1) <= r-l+1) k++;
        return min(rmq2[l][k],rmq2[r-(1<<k)+1][k]);
    }
}
 
void SolveQue ()
{
    #define SKIP_THIS puts("-1");continue;
    long long a, b, ansa, ansb, mxans;
    int la, lb, ra, rb;
    while (q--)
    {
        scanf ("%lld %lld", &a, &b);
        Query (a, la, ra);
        Query (b, lb, rb);
        if (la < 0 || lb < 0) {SKIP_THIS}
        mxans = (long long)(min(ra-la,rb-lb) + 1);
        ansa = min((long long)lcp(la,lb,1), mxans);
        ansb = min((long long)lcp(n-ra-1,n-rb-1,0), mxans);
        printf ("%lld\n", ansa*ansa+ansb*ansb);
    }
}
 
int main ()
{
    Read();
    BuildSa();
    BuildRmq();
    SolveQue();
    return 0;
}
