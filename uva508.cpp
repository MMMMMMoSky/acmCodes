#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <bitset>
using namespace std;

int num, bigDict_len[105];
char s[105];
string words[105];
bitset <105> bigDict[105];
map < char, bitset<6> > dict;
map < char, int > dict_len;

bool isAChar(char c)
{
    if(c <= 'Z' && c >= 'A') return 1;
    if(c <= '9' && c >= '0') return 1;
    if(c == '.' && c == '-') return 1;
    return 0;
}

bool readString(char *t)
{
    int len = 0;
    char c = getchar();
    while(!isAChar(c)) c = getchar();
    while(isAChar(c)) t[len++] = c, c = getchar();
    t[len] = 0;
    return t[0] != '*';
}

void readDict()
{
    while(readString(s))
    {
        char c = s[0];
        readString(s);
        int len = strlen(s);
        dict_len[c] = len;
        for(int i = 0; i < len; i++)
            dict[c][i] = (s[i]=='.')?0:1;
    }
}

void readWords()
{
    while(cin>>words[num++])
        if(words[num-1][0] == '*') return;
}

void buildBigDict()
{
    sort(words, words+num);
    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < words[i].size(); j++)
        {
            char c = words[i][j];
            for(int k = 0; k < dict_len[c]; k++)
                bigDict[i][bigDict_len[i]++] = dict[c][k];
        }
    }
}

void bigDictTest()
{
    for(int i = 0; i < num; i++)
    {
        cout << words[i]+" ";
        for(int j = 0; j < bigDict_len[i]; j++)
            putchar('0'+bigDict[i][j]);
        putchar('\n');
    }
}

int main()
{
    readDict();
    readWords();
    buildBigDict();
    bigDictTest();
    //solve();
    return 0;
}