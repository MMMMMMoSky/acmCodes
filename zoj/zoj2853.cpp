// TLE....
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m, T;
double initM[1][205], multM[205][205], tmpM[205][205], calcM[205][205];

void Matrix_mult(double A[][205], double B[][205], int N, int M, int P)
{
    memset(calcM, 0, sizeof calcM);
    for(int i = 0; i < N; i++)
    for(int k = 0; k < P; k++)
    {
        if(A[i][k] < 1e-6) continue;
        for(int j = 0; j < M; j++)
            if(B[k][j] > 1e-6) calcM[i][j] += A[i][k] * B[k][j];
    }
    for(int i = 0; i < N; i++)
    for(int j = 0; j < P; j++)
        A[i][j] = calcM[i][j];
}

void Matrix_pow(double A[][205], int k, int N)
{
    if(k & 1) {
        double tmp[205][205];
        for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            tmp[i][j] = A[i][j];
        for(k>>=1; k; k>>=1)
            Matrix_mult(tmp, tmp, N, N, N);
        Matrix_mult(A, tmp, N, N, N);
    } else {
        for(k>>=1; k; k>>=1)
            Matrix_mult(A, A, N, N, N);
    }
}

int main()
{
    while(true) {
        scanf("%d %d", &n, &m);
        if(!(n+m)) return 0;
        memset(multM, 0, sizeof multM);
        memset(tmpM,  0, sizeof tmpM);
        for(int i = 0; i < n; i++)
        {
            scanf("%lf", initM[0]+i);
            multM[i][i] = tmpM[i][i] = 1.0;
        }
        scanf("%d", &T); 
        for(int i = 0; i < T; i++)
        {
            int a, b; double c;
            scanf("%d %d %lf", &a, &b, &c);
            tmpM[a][a] -= c, tmpM[a][b] += c; 
            Matrix_mult(multM, tmpM, n, n, n);
            tmpM[a][a] += c, tmpM[a][b] -= c;
        }
        Matrix_pow(multM, m, n);
        Matrix_mult(initM, multM, 1, n, n);
        printf("%.0lf\n", initM[0][n-1]);
    }
}