#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 1000;
const int M = 1000;

int main()
{
    srand(time(NULL));
    int n = (rand()%N)+1;
    int m = (rand()%N)+1;
    printf("%d %d\n", n, m);
    for(int i = 1; i <= n; i++)
        printf("%d ", (rand()%M)+1);
    putchar('\n');
    for(int i = 1; i <= m; i++)
    {
        int t = (rand()&1)+1;
        int a = (rand()%n)+1;
        int b = (rand()%n)+1;
        if(a > b) swap(a, b);
        printf("%d %d %d ", t, a, b);
        if(t == 1) {
            int x = (rand()%M)+1;
            printf("%d", x);
        }
        putchar('\n');
    } 
}
