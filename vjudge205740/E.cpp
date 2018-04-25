#include <cstdio>
#include <cstring>

char names[5][15] = {"Danil", "Olya", "Slava", "Ann", "Nikita"};
int len[5] = {5, 4, 5, 3, 6}, l, cnt;
char s[110];

int cmp(char *A, char *B, int l)
{
    for(int i = 0; i < l; i++)
        if(A[i] != B[i]) return 0;
    return 1;
}

int main()
{
    scanf("%s", s);
    l = strlen(s);
    for(int i = 0; i < l; i++)
    for(int j = 0; j < 5; j++)
        cnt += cmp(s+i, names[j], len[j]);
    printf("%s\n", cnt==1?"YES":"NO");
    return 0;
}