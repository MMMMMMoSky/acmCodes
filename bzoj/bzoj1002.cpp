#include <cstdio>
#include <algorithm>
#include <cstring>
#define P 10000
using namespace std;

struct BigInt
{
	int h, a[25];

	void init (int x)
	{
		h = 1, a[1] = x;
	}

	void init (const BigInt &k)
	{
		h = k.h;
		memset (a, 0, sizeof a);
		for (int i = 1; i <= h; i++) a[i] = k.a[i];
	}

	void mult3 ()
	{
		for (int i = 1; i <= h; i++) a[i] *= 3;
		for (int i = 1; i <= h; i++)
			a[i+1] += a[i]/P, a[i] %= P;
		if (a[h+1]) h++;
	}

	void minu (const BigInt &k)
	{
		for (int i = 1; i <= k.h; i++)
		{
			a[i] -= k.a[i];
			while (a[i] < 0) a[i] += P, a[i+1]--;
		}
		while (a[h] == 0 && h) h--;
	}

	void plus2 ()
	{
		a[1] += 2;
		for (int i = 1; a[i] >= P && i <= h; i++)
		a[i+1] += a[i]/P, a[i] %= P;
		if (a[h+1]) h++;
	}

	void print ()
	{
		printf ("%d", a[h]);
		for (int i = h-1; i > 0; i--)
		printf ("%.4d", a[i]);
		printf ("\n");
	}
};

int N;
BigInt F[105];

int main ()
{
	scanf ("%d", &N);
	F[1].init(1); F[2].init(5);
	for (int i = 3; i <= N; i++)
	{
		F[i].init(F[i-1]);
		F[i].mult3();
		F[i].minu(F[i-2]);
		F[i].plus2();
	}
	F[N].print();
	return 0;
}
